#include "stdafx.h"
#include "CDataShowView.h"

CDataShowView::CDataShowView()
{
	InitializeCriticalSection(&m_critPicture);
}

CDataShowView::~CDataShowView()
{
	removeAllUser();
	for (int i = 0; i < (int)m_pPictureControlArr.size(); i++)
	{
		if (m_pPictureControlArr[i] != NULL)
		{
			delete m_pPictureControlArr[i];
			m_pPictureControlArr[i] = NULL;
		}
	}
	m_pPictureControlArr.clear();
}

bool CDataShowView::addUser(string strUserId, bool isBigPic)
{
	bool bRet = false;
	EnterCriticalSection(&m_critPicture);
	CUpUserInfo* pUpUserInfo = findUpUserInfo(strUserId);

	if (pUpUserInfo == NULL)
	{
		pUpUserInfo = new CUpUserInfo();
		pUpUserInfo->m_strUserId = strUserId;
		pUpUserInfo->m_bBigPic = isBigPic;
		CPicControl* pPicControl = NULL;
		vector<CPicControl*>::iterator iter = m_pPictureControlArr.begin();
		if (iter != m_pPictureControlArr.end())
		{
			pPicControl = *iter;
			m_pPictureControlArr.erase(iter);
		}
		if (pPicControl != NULL)
		{
			pPicControl->m_strUserId = strUserId;
			pPicControl->m_bIsBig = isBigPic;
			pUpUserInfo->m_pPictureControl = pPicControl;
			pPicControl->GetWindowRect(pUpUserInfo->m_showRect);
			m_upUserInfoArr.push_back(pUpUserInfo);
			bRet = true;
		}
		else
		{
			delete pUpUserInfo;
		}
	}
	else
	{
		pUpUserInfo->m_bBigPic = isBigPic;
		bRet = true;
	}
	LeaveCriticalSection(&m_critPicture);
	return bRet;
}

bool CDataShowView::removeUser(string strUserId)
{
	bool bRet = false;
	CUpUserInfo* pUpUserInfo = NULL;
	EnterCriticalSection(&m_critPicture);
	vector<CUpUserInfo*>::iterator iter = m_upUserInfoArr.begin();

	for (; iter != m_upUserInfoArr.end(); iter++)
	{
		if ((*iter)->m_strUserId == strUserId)
		{
			(*iter)->m_pPictureControl->m_strUserId = "";
			(*iter)->m_pPictureControl->m_bIsBig = false;
			(*iter)->m_pPictureControl->MoveWindow(CRect(0, 0, 0, 0), true);
			(*iter)->m_pPictureControl->ShowWindow(SW_HIDE);

			m_pPictureControlArr.push_back((*iter)->m_pPictureControl);
			m_upUserInfoArr.erase(iter);
			bRet = true;
			break;
		}
	}
	LeaveCriticalSection(&m_critPicture);
	return bRet;
}

void CDataShowView::removeAllUser()
{
	EnterCriticalSection(&m_critPicture);
	vector<CUpUserInfo*>::iterator iter = m_upUserInfoArr.begin();

	for (; iter != m_upUserInfoArr.end(); )
	{
		(*iter)->m_pPictureControl->m_strUserId = "";
		(*iter)->m_pPictureControl->m_bIsBig = false;
		(*iter)->m_pPictureControl->MoveWindow(CRect(0, 0, 0, 0), true);
		(*iter)->m_pPictureControl->ShowWindow(SW_HIDE);

		m_pPictureControlArr.push_back((*iter)->m_pPictureControl);
		iter = m_upUserInfoArr.erase(iter);
	}
	LeaveCriticalSection(&m_critPicture);
}

bool CDataShowView::isLeftOneUser(string& strUserId)
{
	bool bLeftOneUser = false;
	int nSize = 0;
	EnterCriticalSection(&m_critPicture);
	nSize = (int)m_upUserInfoArr.size();
	if (nSize == 1)
	{
		strUserId = m_upUserInfoArr[0]->m_strUserId;
		bLeftOneUser = true;
	}
	LeaveCriticalSection(&m_critPicture);
	return bLeftOneUser;
}

int CDataShowView::getUserCount()
{
	int nSize = 0;
	EnterCriticalSection(&m_critPicture);
	nSize = (int)m_upUserInfoArr.size();
	LeaveCriticalSection(&m_critPicture);
	return nSize;
}

string CDataShowView::changeShowStyle(string strUserId, bool bBigPic)
{
	string changeUserId;
	EnterCriticalSection(&m_critPicture);
	vector<CUpUserInfo*>::iterator iter = m_upUserInfoArr.begin();

	for (; iter != m_upUserInfoArr.end(); iter++)
	{
		if (bBigPic && (*iter)->m_bBigPic && strUserId != (*iter)->m_strUserId)
		{
			(*iter)->m_bBigPic = false;
			(*iter)->m_pPictureControl->m_bIsBig = false;
			changeUserId = (*iter)->m_strUserId;
		}
		if (strUserId == (*iter)->m_strUserId)
		{
			(*iter)->m_bBigPic = bBigPic;
			(*iter)->m_pPictureControl->m_bIsBig = bBigPic;
		}
	}
	LeaveCriticalSection(&m_critPicture);
	return changeUserId;
}

void CDataShowView::setDrawRect(CRect drawRect)
{
	m_DrawRect = drawRect;
}

void CDataShowView::setShowPictures()
{
	CUpUserInfo* pUpUserInfo = NULL;
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
	bool bFindMax = false;

	for (int i = 0; i < nSize; i++)
	{
		if (m_upUserInfoArr[i]->m_bBigPic)
		{
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

			m_upUserInfoArr[i]->m_showRect = smallRect;
			m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(smallRect);
			m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);
			useIndex++;
		}
	}
	LeaveCriticalSection(&m_critPicture);
}


CUpUserInfo* CDataShowView::findUpUserInfo(string strUserId)
{
	CUpUserInfo* pUpUserInfo = NULL;
	for (int i = 0; i < (int)m_upUserInfoArr.size(); i++)
	{
		if (m_upUserInfoArr[i]->m_strUserId == strUserId)
		{
			pUpUserInfo = m_upUserInfoArr[i];
			break;
		}
	}
	return pUpUserInfo;
}

void CDataShowView::drawPic(YUV_TYPE type, string userId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	try
	{
		EnterCriticalSection(&m_critPicture);
		CUpUserInfo* pUpUserInfo = findUpUserInfo(userId);
		LeaveCriticalSection(&m_critPicture);
		uint8_t* videoDataRGB = NULL;
		if (pUpUserInfo != NULL && videoData != NULL && videoDataLen > 0)
		{
			videoDataRGB = new uint8_t[w*h * 3];
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
		}

		EnterCriticalSection(&m_critPicture);
		pUpUserInfo = findUpUserInfo(userId);
		if (pUpUserInfo != NULL && pUpUserInfo->m_pPictureControl != NULL)
		{
			if (videoDataRGB != NULL && videoDataLen > 0)
			{
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

void CDataShowView::drawPic(string userId, int w, int h, CImage image)
{
	try
	{
		EnterCriticalSection(&m_critPicture);
		CUpUserInfo* pUpUserInfo = findUpUserInfo(userId);
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
