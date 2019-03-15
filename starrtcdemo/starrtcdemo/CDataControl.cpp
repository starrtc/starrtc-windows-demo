#include "stdafx.h"
#include "CDataControl.h"
#include "CropType.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
using namespace cv;
void MatToCImage(Mat &mat, CImage &cImage)
{
	//create new CImage  
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	cImage.Destroy(); //clear  
	cImage.Create(width,
		height, //positive: left-bottom-up   or negative: left-top-down  
		8 * channels); //numbers of bits per pixel  

	//copy values  
	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); //A pointer to the bitmap buffer  

	//The pitch is the distance, in bytes. represent the beginning of   
	// one bitmap line and the beginning of the next bitmap line  
	int step = cImage.GetPitch();

	for (int i = 0; i < height; ++i)
	{
		ps = (mat.ptr<uchar>(i));
		for (int j = 0; j < width; ++j)
		{
			if (channels == 1) //gray  
			{
				*(pimg + i * step + j) = ps[j];
			}
			else if (channels == 3) //color  
			{
				for (int k = 0; k < 3; ++k)
				{
					*(pimg + i * step + j * 3 + k) = ps[(width - j) * 3 + k];
				}
			}
		}
	}

}

void MatToRGB(Mat &mat, BYTE* data)
{
	//create new CImage  
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();

	//copy values  
	uchar* ps;
	uchar* pimg = data; //A pointer to the bitmap buffer  


	for (int i = 0; i < height; ++i)
	{
		ps = (mat.ptr<uchar>(i));
		for (int j = 0; j < width; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				*(pimg + (i* width + j) * 3 + k) = ps[(width - j) * 3 + k];
			}
		}
	}

}

DWORD WINAPI GetCameraDataThread(LPVOID p)
{
	CLocalDataControl* pDataControl = (CLocalDataControl*)p;

	while (WaitForSingleObject(pDataControl->m_hGetDataEvent, INFINITE) == WAIT_OBJECT_0)
	{
		if (pDataControl->m_bExit)
		{
			break;
		}

		VideoCapture cap;
		cap.open(0);

		Mat frame;

		CImage image;
		pDataControl->addUpId();
		while (pDataControl->m_bExit == false && pDataControl->m_bStop == false)
		{
			cap >> frame;
			//绘制 传递给编码器
			int width = (int)cap.get(CV_CAP_PROP_FRAME_WIDTH);  //帧宽度
			int height = (int)cap.get(CV_CAP_PROP_FRAME_HEIGHT); //帧高度
			double frameRate = cap.get(CV_CAP_PROP_FPS);  //帧率 x frames/s
			if (width <= 0 || height <= 0)
			{
				continue;
			}

			BYTE* data = new BYTE[width*height * 3];
			MatToRGB(frame, data);
			BYTE * src = data;
			pDataControl->putShowPicData(pDataControl->m_CropPicDataQueue, pDataControl->m_csCropPicDataQueue, width, height, (uint8_t*)data, width * height * 3);
			//pDataControl->putShowPicData(pDataControl->m_ShowPicDataQueue, pDataControl->m_csShowPicDataQueue, width, height, (uint8_t*)data, width * height * 3);
			delete[] data;
			data = NULL;
			Sleep(66);
		}
	}
	SetEvent(pDataControl->m_hExitEvent);
	return 0;
}

DWORD WINAPI CropPicThread(LPVOID p)
{
	CLocalDataControl* pDataControl = (CLocalDataControl*)p;

	while (true)
	{
		if (pDataControl->m_bExit)
		{
			break;
		}
		CShowPicData* pCropPicData = NULL;
		EnterCriticalSection(&pDataControl->m_csCropPicDataQueue);//进入临界区	
		int nSize = pDataControl->m_CropPicDataQueue.size();
		if (nSize > 0)
		{
			pCropPicData = pDataControl->m_CropPicDataQueue.front();
			pDataControl->m_CropPicDataQueue.pop();
		}
		LeaveCriticalSection(&pDataControl->m_csCropPicDataQueue);//离开临界区
		if (pCropPicData != NULL)
		{
			CPicSize bigSize;
			CPicSize smallSize;
			CropTypeInfo::getCropSize(pDataControl->m_CropType, bigSize, smallSize);
			//裁剪 VIDEO_CROP_CONFIG_480BW_480BH_120SW_120SH
			int length = (int)(bigSize.m_nWidth * bigSize.m_nHeight * 1.5f);
			int lengthSmall = (int)(smallSize.m_nWidth * smallSize.m_nHeight * 1.5f);
			uint8_t* outVideoDataBig = NULL;
			if (length > 0)
			{
				outVideoDataBig = new uint8_t[length];
			}

			uint8_t* outVideoDataSmall = NULL;
			if (length > 0)
			{
				outVideoDataSmall = new uint8_t[lengthSmall];
			}

			int nRet = pDataControl->cropVideoRawNV12(pCropPicData->m_nWidth, pCropPicData->m_nHeight, pCropPicData->m_pVideoData, pCropPicData->m_nDataLength, (int)pDataControl->m_CropType, 0, 0, outVideoDataBig, outVideoDataSmall);
			
			if (pDataControl->m_bInsertData)
			{
				pDataControl->putInsertPicData(pDataControl->m_SendPicDataQueue, pDataControl->m_csSendPicDataQueue, bigSize.m_nWidth, bigSize.m_nWidth, outVideoDataBig, length,
					smallSize.m_nWidth, smallSize.m_nHeight, outVideoDataSmall, lengthSmall);
			}

			if (outVideoDataBig)
			{
				pDataControl->putShowPicData(pDataControl->m_ShowPicDataQueue, pDataControl->m_csShowPicDataQueue, bigSize.m_nWidth, bigSize.m_nHeight, outVideoDataBig, length);
				
				delete[] outVideoDataBig;
				outVideoDataBig = NULL;
			}

			if (outVideoDataSmall)
			{
				delete[] outVideoDataSmall;
				outVideoDataSmall = NULL;
			}
			delete pCropPicData;
			pCropPicData = NULL;
		}
		else
		{
			Sleep(50);
		}
	}
	return 0;
}

DWORD WINAPI SendPicThread(LPVOID p)
{
	CLocalDataControl* pDataControl = (CLocalDataControl*)p;

	while (true)
	{
		if (pDataControl->m_bExit)
		{
			break;
		}
		CInsertData* pInsertPicData = NULL;
		EnterCriticalSection(&pDataControl->m_csSendPicDataQueue);//进入临界区	
		int nSize = pDataControl->m_SendPicDataQueue.size();
		if (nSize > 0)
		{
			pInsertPicData = pDataControl->m_SendPicDataQueue.front();
			pDataControl->m_SendPicDataQueue.pop();
		}
		LeaveCriticalSection(&pDataControl->m_csSendPicDataQueue);//离开临界区
		if (pInsertPicData != NULL)
		{
			if (pInsertPicData->m_BigPicData != NULL)
			{
				pDataControl->insertVideoRaw(pInsertPicData->m_BigPicData->m_pVideoData, pInsertPicData->m_BigPicData->m_nDataLength, 1);
				delete pInsertPicData->m_BigPicData;
				pInsertPicData->m_BigPicData = NULL;
			}

			if (pInsertPicData->m_SmallPicData != NULL)
			{
				pDataControl->insertVideoRaw(pInsertPicData->m_SmallPicData->m_pVideoData, pInsertPicData->m_SmallPicData->m_nDataLength, 0);
				delete pInsertPicData->m_SmallPicData;
				pInsertPicData->m_SmallPicData = NULL;
			}
			
			//pSendPicData->m_pVideoData = NULL;
			delete pInsertPicData;
			pInsertPicData = NULL;
		}
		else
		{
			Sleep(50);
		}
	}
	return 0;
}

DWORD WINAPI ShowPicThread(LPVOID p)
{
	CLocalDataControl* pDataControl = (CLocalDataControl*)p;

	while (true)
	{
		if (pDataControl->m_bExit)
		{
			break;
		}
		CShowPicData* pShowPicData = NULL;
		EnterCriticalSection(&pDataControl->m_csShowPicDataQueue);//进入临界区	
		int nSize = pDataControl->m_ShowPicDataQueue.size();
		if (nSize > 0)
		{
			pShowPicData = pDataControl->m_ShowPicDataQueue.front();
			pDataControl->m_ShowPicDataQueue.pop();
		}
		LeaveCriticalSection(&pDataControl->m_csShowPicDataQueue);//离开临界区
		if (pShowPicData != NULL)
		{
			pDataControl->drawPic(FMT_NV12, pShowPicData->m_nWidth, pShowPicData->m_nHeight, pShowPicData->m_pVideoData, pShowPicData->m_nDataLength);
			delete pShowPicData;
			pShowPicData = NULL;
		}
		else
		{
			Sleep(50);
		}
	}
	return 0;
}

CLocalDataControl::CLocalDataControl()
{
	m_hGetDataEvent = NULL;
	m_hGetCameraDataThread = NULL;
	m_hExitEvent = NULL;

	m_hCropPicThread = NULL;
	m_hSendPicThread = NULL;
	m_hShowPicThread = NULL;

	InitializeCriticalSection(&m_csCropPicDataQueue);//初始化临界区
	InitializeCriticalSection(&m_csSendPicDataQueue);//初始化临界区
	InitializeCriticalSection(&m_csShowPicDataQueue);//初始化临界区

	m_bStop = false;
	m_bExit = false;
	m_bInsertData = false;

	m_hGetDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hExitEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hGetCameraDataThread = CreateThread(NULL, 0, GetCameraDataThread, (void*)this, 0, 0); // 创建线程

	m_hCropPicThread = CreateThread(NULL, 0, CropPicThread, (void*)this, 0, 0); // 创建线程
	m_hSendPicThread = CreateThread(NULL, 0, SendPicThread, (void*)this, 0, 0); // 创建线程
	m_hShowPicThread = CreateThread(NULL, 0, ShowPicThread, (void*)this, 0, 0); // 创建线程
}


CLocalDataControl::~CLocalDataControl()
{
	m_bInsertData = false;
	m_bStop = true;
	m_bExit = true;

	if (m_hGetDataEvent != NULL)
	{
		SetEvent(m_hGetDataEvent);
		CloseHandle(m_hGetDataEvent);
		m_hGetDataEvent = NULL;
	}

	if (m_hExitEvent != NULL)
	{
		WaitForSingleObject(m_hExitEvent, INFINITE);
		CloseHandle(m_hExitEvent);
		m_hExitEvent = NULL;
	}

	if (m_hGetCameraDataThread != NULL)
	{
		CloseHandle(m_hGetCameraDataThread);
		m_hGetCameraDataThread = NULL;
	}

	if (m_hCropPicThread != NULL)
	{
		WaitForSingleObject(m_hCropPicThread, INFINITE);
		CloseHandle(m_hCropPicThread);
		m_hCropPicThread = NULL;
	}
	clearShowPicDataQueue(m_CropPicDataQueue, m_csCropPicDataQueue);
	DeleteCriticalSection(&m_csCropPicDataQueue);//删除临界区


	if (m_hSendPicThread != NULL)
	{
		WaitForSingleObject(m_hSendPicThread, INFINITE);
		CloseHandle(m_hSendPicThread);
		m_hSendPicThread = NULL;
	}
	clearInsertPicDataQueue(m_SendPicDataQueue, m_csSendPicDataQueue);
	DeleteCriticalSection(&m_csSendPicDataQueue);//删除临界区

	if (m_hShowPicThread != NULL)
	{
		WaitForSingleObject(m_hShowPicThread, INFINITE);
		CloseHandle(m_hShowPicThread);
		m_hShowPicThread = NULL;
	}
	clearShowPicDataQueue(m_ShowPicDataQueue, m_csShowPicDataQueue);
	DeleteCriticalSection(&m_csShowPicDataQueue);//删除临界区
}

void CLocalDataControl::startGetData(CROP_TYPE cropType, bool bInsert)
{
	m_bStop = false;
	SetEvent(m_hGetDataEvent);
	m_bInsertData = bInsert;
	m_CropType = cropType;
}

void CLocalDataControl::stopGetData()
{
	clearShowPicDataQueue(m_CropPicDataQueue, m_csCropPicDataQueue);
	clearInsertPicDataQueue(m_SendPicDataQueue, m_csSendPicDataQueue);
	clearShowPicDataQueue(m_ShowPicDataQueue, m_csShowPicDataQueue);
	m_bStop = true;
	m_bInsertData = false;
}

/*
 * 将显示图片放入队列
 */
void CLocalDataControl::putShowPicData(queue<CShowPicData*>& picDataQueue, CRITICAL_SECTION& cs, int width, int height, uint8_t* videoData, int dataLength)
{
	EnterCriticalSection(&cs);//进入临界区
	CShowPicData* pShowPicData = new CShowPicData(width, height, videoData, dataLength);
	picDataQueue.push(pShowPicData);
	LeaveCriticalSection(&cs);//离开临界区
}

/*
 * 清空显示图片队列
 */
void CLocalDataControl::clearShowPicDataQueue(queue<CShowPicData*>& picDataQueue, CRITICAL_SECTION& cs)
{
	EnterCriticalSection(&cs);//进入临界区
	int nSize = picDataQueue.size();

	for (int i = 0; i < nSize; i++)
	{
		CShowPicData* pTemp = picDataQueue.front();
		if (pTemp != NULL)
		{
			delete pTemp;
			pTemp = NULL;
		}
		picDataQueue.pop();
	}
	LeaveCriticalSection(&cs);//离开临界区
}

/*
 * 将显示图片放入队列
 */
void CLocalDataControl::putInsertPicData(queue<CInsertData*>& picDataQueue, CRITICAL_SECTION& cs, int widthBig, int heightBig, uint8_t* videoDataBig, int dataLengthBig, int widthSmall, int heightSmall, uint8_t* videoDataSmall, int dataLengthSmall)
{
	EnterCriticalSection(&cs);//进入临界区
	CInsertData* pInsertData = new CInsertData();
	if (dataLengthBig > 0)	
	{
		CShowPicData* pShowPicDataBig = new CShowPicData(widthBig, heightBig, videoDataBig, dataLengthBig);
		pInsertData->m_BigPicData = pShowPicDataBig;
	}
	if (dataLengthSmall > 0)
	{
		CShowPicData* pShowPicDataSmall = new CShowPicData(widthSmall, heightSmall, videoDataSmall, dataLengthSmall);
		pInsertData->m_SmallPicData = pShowPicDataSmall;

	}
	
	picDataQueue.push(pInsertData);
	LeaveCriticalSection(&cs);//离开临界区
}

/*
 * 清空显示图片队列
 */
void CLocalDataControl::clearInsertPicDataQueue(queue<CInsertData*>& picDataQueue, CRITICAL_SECTION& cs)
{
	EnterCriticalSection(&cs);//进入临界区
	int nSize = picDataQueue.size();

	for (int i = 0; i < nSize; i++)
	{
		CInsertData* pTemp = picDataQueue.front();
		if (pTemp != NULL)
		{
			if (pTemp->m_BigPicData != NULL)
			{
				delete pTemp->m_BigPicData;
				pTemp->m_BigPicData = NULL;
			}

			if (pTemp->m_SmallPicData != NULL)
			{
				delete pTemp->m_SmallPicData;
				pTemp->m_SmallPicData = NULL;
			}
			delete pTemp;
			pTemp = NULL;
		}
		picDataQueue.pop();
	}
	LeaveCriticalSection(&cs);//离开临界区
}
