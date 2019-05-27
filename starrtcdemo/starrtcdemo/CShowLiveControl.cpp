#include "stdafx.h"
#include "CShowLiveControl.h"


CShowLiveControl::CShowLiveControl()
{
	m_showType = LIVE_SHOW_TYPE_LIVE;
	memset(m_pPictureControlArr, 0, sizeof(m_pPictureControlArr));
	memset(m_configArr, 0, sizeof(m_configArr));
	m_configArr[0] = 2;
	InitializeCriticalSection(&m_critPicture);
}


CShowLiveControl::~CShowLiveControl()
{
	removeAllUpUser();
	for (int i = 0; i < UPID_MAX_SIZE; i++)
	{
		if (m_pPictureControlArr[i] != NULL)
		{
			//delete m_pPictureControlArr[i];
			m_pPictureControlArr[i] = NULL;
		}
	}
}

void CShowLiveControl::setDrawRect(CRect drawRect)
{
	m_DrawRect = drawRect;
}

void CShowLiveControl::setShowPictures()
{
	if (m_showType == LIVE_SHOW_TYPE_LIVE)
	{
		setLiveShow();
	}
	else
	{
		setVoipShow();
	}
}

void CShowLiveControl::setVoipShow()
{
	CUpUserInfo* pUpUserInfo = NULL;
	int useIndex = 1;

	/*EnterCriticalSection(&m_critPicture);
	int nSize = (int)m_upUserInfoArr.size();
	CRect rect = m_DrawRect;

	int nWidth = (int)(rect.Width()*0.3f);

	for (int i = 0; i < nSize; i++)
	{
		if (m_configArr[m_upUserInfoArr[i]->m_upid] == 2)
		{
			m_upUserInfoArr[i]->m_pPictureControl = m_pPictureControlArr[0];
			m_upUserInfoArr[i]->m_pPictureControl->m_upId = 0;
			m_upUserInfoArr[i]->m_bBigPic = true;
			m_upUserInfoArr[i]->m_nTimes = 0;
			m_upUserInfoArr[i]->m_showRect = rect;
			m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(rect);
			m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);

		}
		else
		{
			CRect smallRect;
			smallRect.left = rect.left + ((useIndex - 1)%3)*nWidth;
			smallRect.top = rect.top + (long)(useIndex / 4.0f * m_DrawRect.Height()*0.25f);
			smallRect.right = smallRect.left + nWidth;
			smallRect.bottom = smallRect.top + (long)(m_DrawRect.Height()*0.25f);

			m_upUserInfoArr[i]->m_bBigPic = false;
			m_upUserInfoArr[i]->m_pPictureControl = m_pPictureControlArr[useIndex];
			m_upUserInfoArr[i]->m_pPictureControl->m_upId = m_upUserInfoArr[i]->m_upid;
			useIndex++;
			m_upUserInfoArr[i]->m_showRect = smallRect;
			m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(smallRect);
			m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);
		}
	}
	LeaveCriticalSection(&m_critPicture);*/
}
void CShowLiveControl::setLiveShow()
{
	/*CUpUserInfo* pUpUserInfo = NULL;
	int useIndex = 1;

	EnterCriticalSection(&m_critPicture);
	int nSize = (int)m_upUserInfoArr.size();
	CRect rect = m_DrawRect;

	int nWidth = (int)(rect.Width()*0.25f);

	if (nSize > 1 && nSize <= 4)
	{
		rect.bottom = m_DrawRect.bottom - (long)(m_DrawRect.Height()*0.25f);
	}
	else if (nSize > 4)
	{
		rect.bottom = m_DrawRect.bottom - (long)(m_DrawRect.Height()*0.5f);
	}
	for (int i = 0; i < nSize; i++)
	{
		if (m_configArr[m_upUserInfoArr[i]->m_upid] == 2)
		{
			m_upUserInfoArr[i]->m_pPictureControl = m_pPictureControlArr[0];
			m_upUserInfoArr[i]->m_pPictureControl->m_upId = 0;
			m_upUserInfoArr[i]->m_bBigPic = true;
			m_upUserInfoArr[i]->m_nTimes = 0;
			m_upUserInfoArr[i]->m_showRect = rect;
			m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(rect);
			m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);

		}
		else
		{
			CRect smallRect;
			smallRect.left = rect.left + (useIndex - 1)*nWidth;
			smallRect.top = rect.bottom;
			if (useIndex > 4)
			{
				smallRect.top = rect.bottom + (long)(useIndex / 4.0f * m_DrawRect.Height()*0.25f);
			}
			smallRect.right = smallRect.left + nWidth;
			smallRect.bottom = smallRect.top + (long)(m_DrawRect.Height()*0.25f);

			m_upUserInfoArr[i]->m_bBigPic = false;
			m_upUserInfoArr[i]->m_pPictureControl = m_pPictureControlArr[useIndex];
			m_upUserInfoArr[i]->m_pPictureControl->m_upId = m_upUserInfoArr[i]->m_upid;
			useIndex++;
			m_upUserInfoArr[i]->m_showRect = smallRect;
			m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(smallRect);
			m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);
		}
	}
	LeaveCriticalSection(&m_critPicture);*/
}

void CShowLiveControl::resetPicControlPos()
{
	m_pPictureControlArr[0]->MoveWindow(m_DrawRect);
	m_pPictureControlArr[0]->ShowWindow(SW_SHOW);
	for (int i = 1; i < 7; i++)
	{
		m_pPictureControlArr[i]->MoveWindow(CRect(0, 0, 0, 0), true);
		m_pPictureControlArr[i]->ShowWindow(SW_HIDE);
	}
}

void CShowLiveControl::addUpId(int nUpId)
{
	/*CUpUserInfo* pUpUserInfo = findUpUserInfo(nUpId);

	if (pUpUserInfo == NULL)
	{
		pUpUserInfo = new CUpUserInfo();
		pUpUserInfo->m_upid = nUpId;
		CRect rect;
		m_pPictureControlArr[nUpId]->GetWindowRect(rect);
		pUpUserInfo->m_showRect = rect;
		pUpUserInfo->m_pPictureControl = m_pPictureControlArr[nUpId];// pProcessInfo->m_pPictureControl;
		m_upUserInfoArr.push_back(pUpUserInfo);
	}
	pUpUserInfo->m_bUse = true;*/
}

CUpUserInfo* CShowLiveControl::findUpUserInfo(int upid)
{
	CUpUserInfo* pUpUserInfo = NULL;
	/*for (int i = 0; i < (int)m_upUserInfoArr.size(); i++)
	{
		if (m_upUserInfoArr[i]->m_upid == upid)
		{
			pUpUserInfo = m_upUserInfoArr[i];
			break;
		}
	}*/
	return pUpUserInfo;
}

bool CShowLiveControl::removeAllUpUser()
{
	bool bRet = true;
	/*CUpUserInfo* pUpUserInfo = NULL;
	EnterCriticalSection(&m_critPicture);
	vector<CUpUserInfo*>::iterator iter = m_upUserInfoArr.begin();

	for (; iter != m_upUserInfoArr.end(); iter++)
	{
		(*iter)->m_pPictureControl->m_upId = -1;
		(*iter)->m_pPictureControl->MoveWindow(CRect(0, 0, 0, 0), true);
		(*iter)->m_pPictureControl->ShowWindow(SW_HIDE);
	}
	m_upUserInfoArr.clear();
	LeaveCriticalSection(&m_critPicture);*/
	return bRet;
}

bool CShowLiveControl::removeUpUser(int upid)
{
	bool bRet = false;
	/*CUpUserInfo* pUpUserInfo = NULL;
	EnterCriticalSection(&m_critPicture);
	vector<CUpUserInfo*>::iterator iter = m_upUserInfoArr.begin();

	for (; iter != m_upUserInfoArr.end(); iter++)
	{
		if ((*iter)->m_upid == upid)
		{
			(*iter)->m_pPictureControl->m_upId = -1;
			(*iter)->m_pPictureControl->MoveWindow(CRect(0, 0, 0, 0), true);
			(*iter)->m_pPictureControl->ShowWindow(SW_HIDE);
			m_upUserInfoArr.erase(iter);
			bRet = true;
			break;
		}
	}
	LeaveCriticalSection(&m_critPicture);*/
	return bRet;
}

void CShowLiveControl::drawPic(YUV_TYPE type, int upid, int w, int h, uint8_t* videoData, int videoDataLen)
{
	try
	{
		EnterCriticalSection(&m_critPicture);

		CUpUserInfo* pUpUserInfo = findUpUserInfo(upid);
		if (pUpUserInfo != NULL && pUpUserInfo->m_pPictureControl != NULL)
		{
			if (videoData != NULL && videoDataLen > 0)
			{
				uint8_t* videoDataRGB = new uint8_t[w*h * 3];
				if (type == FMT_NV12 || type == FMT_NV21)
				{
					CUtil::yuv420sp_to_rgb24(type, videoData, videoDataRGB, w, h);
				}
				else if (type == FMT_YUV420P)
				{
					CUtil::yuv420p_to_rgb24(videoData, videoDataRGB, w, h);
				}
				else
				{
					memcpy(videoDataRGB, videoData, sizeof(uint8_t)*videoDataLen);
				}



				CRect rect;

				pUpUserInfo->m_pPictureControl->GetClientRect(&rect);     //m_picture为Picture Control控件变量，获得控件的区域对象
				CImage image;       //使用图片类
				image.Create(w, h, 24, 0);
				//首地址  
				byte* pRealData = (byte*)image.GetBits();
				//首地址    
				//行距  
				int pit = image.GetPitch();
				for (int i = 0; i < w; i++)
				{
					for (int j = 0; j < h; j++)
					{
						*(pRealData + pit * j + i * 3) = (int)videoDataRGB[3 * j*w + 3 * i];
						*(pRealData + pit * j + i * 3 + 1) = (int)videoDataRGB[3 * j*w + 3 * i + 1];
						*(pRealData + pit * j + i * 3 + 2) = (int)videoDataRGB[3 * j*w + 3 * i + 2];
					}
				}

				int width = w;
				int height = h;
				float scale = 0.0f;
				float heightScale = 0.0f;

				float rectScale = 1.0f;

				float widthTextureEdge = 0.0;
				float heightTextureEdge = 0.0;

				float widthEdge = 0.0;
				float heightEdge = 0.0;

				if (w < rect.Width() && h < rect.Height())
				{
					width = w;
					height = h;
					widthEdge = (rect.Width() - width) / 2.0f;
					heightEdge = (rect.Height() - height) / 2.0f;
				}
				else
				{
					if (w > 0)
					{
						scale = ((float)rect.Width()) / ((float)w);
					}

					if (h > 0)
					{
						float heightScale = ((float)rect.Height()) / ((float)h);
						if (scale < heightScale)
						{
							rectScale = scale;
							width = (int)(w * scale);
							widthEdge = (rect.Width() - width) / 2.0f;

							height = (int)(h * scale);
							heightEdge = (rect.Height() - height) / 2.0f;
						}
						else
						{
							rectScale = heightScale;
							width = (int)(w * heightScale);
							widthEdge = (rect.Width() - width) / 2.0f;

							height = (int)(h * heightScale);
							heightEdge = (rect.Height() - height) / 2.0f;
						}
					}
				}

				CDC* pDC = pUpUserInfo->m_pPictureControl->GetWindowDC();    //获得显示控件的DC


				CDC MemDC;
				CBitmap memBitmap;

				MemDC.CreateCompatibleDC(pDC);         // 利用屏幕DC创建内存DC
				memBitmap.CreateCompatibleBitmap(         // 利用屏幕DC创建兼容的位图
					pDC,
					rect.Width(),
					rect.Height());

				MemDC.SelectObject(&memBitmap);            // 让内存DC输出到位图
				MemDC.SetStretchBltMode(COLORONCOLOR);
				// 使用MemDC画图
				// 。。。。。。
				FillRect(MemDC.m_hDC, &rect, CBrush(RGB(0, 0, 0)));

				image.Draw(MemDC.m_hDC, (int)widthEdge, (int)heightEdge, width, height, 0, 0, w, h);      //图片类的图片绘制Draw函数
				//COLORREF col = RGB(255, 0, 0);
				//CPen pen(PS_SOLID, 2, col);
				/*if (pUpUserInfo->m_bBigPic)
				{
					CBrush br;
					CPen pen;
					pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
					br.CreateStockObject(NULL_BRUSH);

					CPen* pOldPen = MemDC.SelectObject(&pen);
					CBrush* pOldBrush = MemDC.SelectObject(&br);
					CRect rect1;
					EnterCriticalSection(&m_critFaceFeature);
					for (int i = 0; i < (int)m_vFindFaceResult.size(); i++)
					{
						rect1.left = m_vFindFaceResult[i].pos[0] * rectScale + widthEdge;
						rect1.top = m_vFindFaceResult[i].pos[1] * rectScale + heightEdge;
						rect1.right = rect1.left + (m_vFindFaceResult[i].pos[2] - m_vFindFaceResult[i].pos[0])*rectScale;
						rect1.bottom = (m_vFindFaceResult[i].pos[3] - m_vFindFaceResult[i].pos[1])*rectScale + rect1.top;

						MemDC.Rectangle(rect1);
						MemDC.TextOut(rect1.left, rect1.top - 10, m_vFindFaceResult[i].name.c_str());
					}
					LeaveCriticalSection(&m_critFaceFeature);
					MemDC.SelectObject(pOldPen);
					MemDC.SelectObject(pOldBrush);
				}*/


				pDC->BitBlt(                                // 从内存DC复制到窗口DC
					0, 0,
					rect.Width(),
					rect.Height(),
					&MemDC,
					0, 0,
					SRCCOPY);

				pUpUserInfo->m_pPictureControl->ReleaseDC(pDC);
				delete[] videoDataRGB;
				videoDataRGB = NULL;
			}
			else
			{
				CRect rect;
				pUpUserInfo->m_pPictureControl->GetClientRect(&rect);
				CDC* pDC = pUpUserInfo->m_pPictureControl->GetWindowDC();    //获得显示控件的DC
				pDC->SetStretchBltMode(COLORONCOLOR);
				FillRect(pDC->m_hDC, &rect, CBrush(RGB(0, 0, 0)));
				pUpUserInfo->m_pPictureControl->ReleaseDC(pDC);

			}
		}
		LeaveCriticalSection(&m_critPicture);
	}
	catch (char *str)
	{
		printf(str);
	}

}

void CShowLiveControl::drawPic(int upid, int w, int h, CImage image)
{
	try
	{
		EnterCriticalSection(&m_critPicture);

		CUpUserInfo* pUpUserInfo = findUpUserInfo(upid);
		if (pUpUserInfo != NULL && pUpUserInfo->m_pPictureControl != NULL)
		{
			CRect rect;
			pUpUserInfo->m_pPictureControl->GetClientRect(&rect);     //m_picture为Picture Control控件变量，获得控件的区域对象

			int width = w;
			int height = h;
			float scale = 0.0f;
			float heightScale = 0.0f;

			float rectScale = 1.0f;

			float widthTextureEdge = 0.0;
			float heightTextureEdge = 0.0;

			float widthEdge = 0.0;
			float heightEdge = 0.0;

			if (w < rect.Width() && h < rect.Height())
			{
				width = w;
				height = h;
				widthEdge = (rect.Width() - width) / 2.0f;
				heightEdge = (rect.Height() - height) / 2.0f;
			}
			else
			{
				if (w > 0)
				{
					scale = ((float)rect.Width()) / ((float)w);
				}

				if (h > 0)
				{
					float heightScale = ((float)rect.Height()) / ((float)h);
					if (scale < heightScale)
					{
						rectScale = scale;
						width = (int)(w * scale);
						widthEdge = (rect.Width() - width) / 2.0f;

						height = (int)(h * scale);
						heightEdge = (rect.Height() - height) / 2.0f;
					}
					else
					{
						rectScale = heightScale;
						width = (int)(w * heightScale);
						widthEdge = (rect.Width() - width) / 2.0f;

						height = (int)(h * heightScale);
						heightEdge = (rect.Height() - height) / 2.0f;
					}
				}
			}

			CDC* pDC = pUpUserInfo->m_pPictureControl->GetWindowDC();    //获得显示控件的DC


			CDC MemDC;
			CBitmap memBitmap;

			MemDC.CreateCompatibleDC(pDC);         // 利用屏幕DC创建内存DC
			memBitmap.CreateCompatibleBitmap(         // 利用屏幕DC创建兼容的位图
				pDC,
				rect.Width(),
				rect.Height());

			MemDC.SelectObject(&memBitmap);            // 让内存DC输出到位图
			MemDC.SetStretchBltMode(COLORONCOLOR);
			// 使用MemDC画图
			// 。。。。。。
			FillRect(MemDC.m_hDC, &rect, CBrush(RGB(0, 0, 0)));

			image.Draw(MemDC.m_hDC, (int)widthEdge, (int)heightEdge, width, height, 0, 0, w, h);      //图片类的图片绘制Draw函数

			pDC->BitBlt(                                // 从内存DC复制到窗口DC
				0, 0,
				rect.Width(),
				rect.Height(),
				&MemDC,
				0, 0,
				SRCCOPY);

			pUpUserInfo->m_pPictureControl->ReleaseDC(pDC);


		}
		LeaveCriticalSection(&m_critPicture);
	}
	catch (char *str)
	{
		printf(str);
	}
}
