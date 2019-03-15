#pragma once
#include <stdint.h>
#include <queue>
#include "CUtil.h"
#include "CropType.h"
using namespace std;
class CShowPicData
{
public:
	CShowPicData(int width, int height, uint8_t* videoData, int dataLength, bool isBig=true)
	{
		m_bIsBig = isBig;
		m_nWidth = width;
		m_nHeight = height;
		m_nDataLength = dataLength;
		m_pVideoData = new uint8_t[dataLength];
		memset(m_pVideoData, 0, sizeof(uint8_t)*dataLength);
		memcpy(m_pVideoData, videoData, sizeof(uint8_t)*dataLength);
	}
	~CShowPicData()
	{
		if (m_pVideoData != NULL)
		{
			delete[] m_pVideoData;
			m_pVideoData = NULL;
		}
	}
public:
	int m_nWidth;
	int m_nHeight;
	uint8_t* m_pVideoData;
	int m_nDataLength;
	bool m_bIsBig;
};
class CInsertData
{
public:
	CInsertData()
	{
		m_BigPicData = NULL;
		m_SmallPicData = NULL;
	}
public:
	CShowPicData* m_BigPicData;
	CShowPicData* m_SmallPicData;
};
class CLocalDataControl
{
public:
	CLocalDataControl();
	virtual ~CLocalDataControl();

	void startGetData(CROP_TYPE cropType, bool bInsert);
	void stopGetData();
	/*
	 * 将显示图片放入队列
	 */
	void putShowPicData(queue<CShowPicData*>& picDataQueue, CRITICAL_SECTION& cs, int width, int height, uint8_t* videoData, int dataLength);

	/*
	 * 清空显示图片队列
	 */
	void clearShowPicDataQueue(queue<CShowPicData*>& picDataQueue, CRITICAL_SECTION& cs);

	/*
	 * 将显示图片放入队列
	 */
	void putInsertPicData(queue<CInsertData*>& picDataQueue, CRITICAL_SECTION& cs, int widthBig, int heightBig, uint8_t* videoDataBig, int dataLengthBig, int widthSmall, int heightSmall, uint8_t* videoDataSmall, int dataLengthSmall);

	/*
	 * 清空显示图片队列
	 */
	void clearInsertPicDataQueue(queue<CInsertData*>& picDataQueue, CRITICAL_SECTION& cs);
	virtual void addUpId() = 0;
	virtual void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig) = 0;
	virtual int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall) = 0;
	virtual void drawPic(YUV_TYPE type, int w, int h, uint8_t* videoData, int videoDataLen) = 0;
public:
	HANDLE m_hGetCameraDataThread;
	HANDLE m_hGetDataEvent;
	HANDLE m_hExitEvent;

	queue<CShowPicData*> m_CropPicDataQueue;
	CRITICAL_SECTION m_csCropPicDataQueue;

	queue<CInsertData*> m_SendPicDataQueue;
	CRITICAL_SECTION m_csSendPicDataQueue;

	queue<CShowPicData*> m_ShowPicDataQueue;
	CRITICAL_SECTION m_csShowPicDataQueue;

	HANDLE m_hCropPicThread;
	HANDLE m_hSendPicThread;
	HANDLE m_hShowPicThread;

	bool m_bExit;
	bool m_bStop;
	bool m_bInsertData;
	CROP_TYPE m_CropType;
};

