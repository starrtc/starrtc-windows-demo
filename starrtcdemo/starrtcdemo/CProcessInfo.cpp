#include "stdafx.h"
#include "CProcessInfo.h"
#include "CUtil.h"
#define USER_DEF_RESOURCE_ID 1000

DWORD WINAPI ThreadFunc(LPVOID p)
{
	static int resId = USER_DEF_RESOURCE_ID + 10;
	CProcessInfo* pProcessInfo = (CProcessInfo*)p;
	while (!pProcessInfo->m_bExit)
	{
		CRecvData* pRecvData = NULL;
		if (pProcessInfo->m_recvDataQueue.size() > 0)
		{
			EnterCriticalSection(&pProcessInfo->m_crit);
			pRecvData = pProcessInfo->m_recvDataQueue.front();
			pProcessInfo->m_recvDataQueue.pop();
			LeaveCriticalSection(&pProcessInfo->m_crit);

			if (pRecvData != NULL)
			{
				int nType = 0;
				uint8_t* pTemp = pRecvData->m_pData;
				memcpy(&nType, pTemp, sizeof(nType));

				pTemp = pTemp + sizeof(nType);

				switch ((SEND_MESSAGE_TYPE)nType)
				{
				case CHILD_PROCESS_LOGIN_FAILED:
				{
					AfxMessageBox("登录失败");
				}
				break;
				case CHILD_PROCESS_JOIN_CHATROOM_FAILED:
				{
					AfxMessageBox("join chat room failed!");
				}
				break;
				case CHILD_PROCESS_APPLAY_DOWNLOAD_FAILED:
				{
					AfxMessageBox("applay download failed!");
				}
				break;
				case CHILD_PROCESS_STOP_CHATROOM_FAILED:
				{
					AfxMessageBox("applay download failed!");
				}
				break;
				case CHILD_PROCESS_STOP_APPLAY_DOWNLOAD_FAILED:
				{
					AfxMessageBox("stop download failed!");
				}
				break;
				case CHILD_PROCESS_CHANNEL_CLOSE:
				case CHILD_PROCESS_CHANNEL_LEAVE:
				case CHILD_PROCESS_REQUEST_LEAVE_SUCCESS:
				{
					pProcessInfo->liveExit();
				}
				break;

				case CHILD_PROCESS_INIT_SUCCESS:
				{
					pProcessInfo->m_bInit = true;
				}
				break;

				case CHILD_PROCESS_START_LIVE_SUCCESS:
				{
					pProcessInfo->setStreamConfig();
				}
				break;

				case CHILD_PROCESS_ADD_UPID:
				{
					if (pProcessInfo->m_bInit)
					{
						int upid = 0;
						memcpy(&upid, pTemp, sizeof(upid));

						CUpUserInfo* pUpUserInfo = pProcessInfo->findUpUserInfo(upid);

						if (pUpUserInfo == NULL)
						{
							pUpUserInfo = new CUpUserInfo();
							pUpUserInfo->m_upid = upid;
							CRect rect;
							pProcessInfo->m_pPictureControlArr[upid]->GetWindowRect(rect);
							pUpUserInfo->m_showRect = rect;
							pUpUserInfo->m_bUse = true;
							pUpUserInfo->m_pPictureControl = pProcessInfo->m_pPictureControlArr[upid];// pProcessInfo->m_pPictureControl;
							resId += 1;
							pProcessInfo->m_upUserInfoArr.push_back(pUpUserInfo);
						}
						else
						{
							pUpUserInfo->m_showRect = pProcessInfo->m_DrawRect;
							pUpUserInfo->m_bUse = true;
						}
						pProcessInfo->setShowPictures();
					}
				}
				break;
				case CHILD_PROCESS_REMOVE_UPID:
				{
					if (pProcessInfo->m_bInit)
					{
						int upid = 0;
						memcpy(&upid, pTemp, sizeof(upid));

						bool bRet = pProcessInfo->removeUpUser(upid);
						pProcessInfo->setShowPictures();
					}
				}
				break;
				case CHILD_PROCESS_REGISTER_FACE_FEATURE:
				{
					int nRet = 0;
					memcpy(&nRet, pTemp, sizeof(nRet));
					if (nRet != 1)
					{
						AfxMessageBox("注册是人脸信息失败");
					}
					else
					{
						AfxMessageBox("注册是人脸信息成功");
					}
				}
				break;
				case CHILD_PROCESS_FACE_FEATURE_INIT_FAILED:
					AfxMessageBox("请检查人脸识别配置环境");
					break;
				case CHILD_PROCESS_FACE_FEATURE:
				{

					int vResultSize = 0;

					char strName[256] = { 0 };
					EnterCriticalSection(&pProcessInfo->m_critFaceFeature);
					pProcessInfo->m_vFindFaceResult.clear();
					int nDataLength = 0;

					memcpy(&vResultSize, pTemp, sizeof(vResultSize));
					pTemp = pTemp + sizeof(vResultSize);
					for (int i = 0; i < vResultSize; i++)
					{
						CFindFaceResult result;
						memcpy(&result.id, pTemp, sizeof(result.id));
						pTemp = pTemp + sizeof(result.id);

						memcpy(result.pos, pTemp, sizeof(result.pos));
						pTemp = pTemp + sizeof(result.pos);

						memset(strName, 0, sizeof(strName));
						memcpy(strName, pTemp, sizeof(strName));
						pTemp = pTemp + sizeof(strName);
						result.name = strName;
						pProcessInfo->m_vFindFaceResult.push_back(result);
					}
					LeaveCriticalSection(&pProcessInfo->m_critFaceFeature);
				}
				break;
				case CHILD_PROCESS_RECV_VIDEO_DATA:
				{
					if (pProcessInfo->m_bInit)
					{
						int upid = 0;
						int w = 0;
						int h = 0;
						int vResultSize = 0;

						char strName[256] = { 0 };

						int nDataLength = 0;

						memcpy(&upid, pTemp, sizeof(upid));
						pTemp = pTemp + sizeof(upid);

						memcpy(&w, pTemp, sizeof(w));
						pTemp = pTemp + sizeof(w);

						memcpy(&h, pTemp, sizeof(h));
						pTemp = pTemp + sizeof(h);

						memcpy(&nDataLength, pTemp, sizeof(nDataLength));
						pTemp = pTemp + sizeof(nDataLength);
						uint8_t* pData = NULL;
						if (nDataLength > 0)
						{
							pData = new uint8_t[nDataLength];

							memcpy(pData, pTemp, nDataLength);

							pProcessInfo->drawPic(upid, w, h, pData, nDataLength);
							delete[] pData;
							pData = NULL;
						}
					}
				}
				break;
				default:
					break;

				}
				delete pRecvData;
				pRecvData = NULL;
			}
		}
		else
		{
			Sleep(20);
		}
	}
	pProcessInfo->m_bThreadExit = true;
	return 0;
}


CProcessInfo::CProcessInfo(CWnd* pParentWnd, CRect drawRect)
{
	m_pParentWnd = pParentWnd;
	m_DrawRect = drawRect;
	m_strWindowName = "";
	m_pPi = NULL;
	m_pPictureControl = NULL;
	m_bExit = false;
	m_bThreadExit = false;
	m_bUse = false;
	m_bInit = false;
	m_bStartFindFace = false;
	memset(m_pPictureControlArr, 0, sizeof(CStatic*)*UPID_MAX_SIZE);
	memset(m_configArr, 0, sizeof(int)*UPID_MAX_SIZE);
	m_configArr[0] = 2;
	InitializeCriticalSection(&m_crit);
	InitializeCriticalSection(&m_critPicture);
	InitializeCriticalSection(&m_critFaceFeature);
	m_hThread = CreateThread(NULL, 0, ThreadFunc, (void*)this, 0, 0); // 创建线程

}


CProcessInfo::~CProcessInfo()
{
	m_bExit = true;
	m_strWindowName = "";
	m_pPictureControl = NULL;
	m_pPi = NULL;
	m_bUse = false;

	while (1)
	{
		if (m_bThreadExit)
		{
			break;
		}
		Sleep(10);
	}
	//WaitForSingleObject(m_hThread, INFINITE);

	while (m_recvDataQueue.size() > 0)
	{
		EnterCriticalSection(&m_crit);
		CRecvData* pRecvData = m_recvDataQueue.front();
		m_recvDataQueue.pop();
		LeaveCriticalSection(&m_crit);
		if (pRecvData != NULL)
		{
			delete pRecvData;
			pRecvData = NULL;
		}
	}
	clearFaceFeatureVector();
}

void CProcessInfo::clearFaceFeatureVector()
{
	EnterCriticalSection(&m_critFaceFeature);
	m_vFindFaceResult.clear();
	LeaveCriticalSection(&m_critFaceFeature);
}

bool CProcessInfo::setData(uint8_t* pData, int nDataLength)
{
	if (pData != NULL && nDataLength > 0)
	{
		CRecvData* pRecvData = new CRecvData();
		if (pRecvData != NULL)
		{
			pRecvData->setData(pData, nDataLength);
			EnterCriticalSection(&m_crit);
			m_recvDataQueue.push(pRecvData);
			LeaveCriticalSection(&m_crit);
		}
	}
	return true;
}

CUpUserInfo* CProcessInfo::findUpUserInfo(int upid)
{
	CUpUserInfo* pUpUserInfo = NULL;
	for (int i = 0; i < (int)m_upUserInfoArr.size(); i++)
	{
		if (m_upUserInfoArr[i]->m_upid == upid)
		{
			pUpUserInfo = m_upUserInfoArr[i];
			break;
		}
	}
	return pUpUserInfo;
}

bool CProcessInfo::removeAllUpUser()
{
	bool bRet = true;
	CUpUserInfo* pUpUserInfo = NULL;
	EnterCriticalSection(&m_critPicture);
	vector<CUpUserInfo*>::iterator iter = m_upUserInfoArr.begin();

	for (; iter != m_upUserInfoArr.end(); iter++)
	{
		(*iter)->m_pPictureControl->m_upId = -1;
		(*iter)->m_pPictureControl->MoveWindow(CRect(0, 0, 0, 0), true);
		(*iter)->m_pPictureControl->ShowWindow(SW_HIDE);
	}
	m_upUserInfoArr.clear();
	LeaveCriticalSection(&m_critPicture);
	return bRet;
}

bool CProcessInfo::removeUpUser(int upid)
{
	bool bRet = false;
	CUpUserInfo* pUpUserInfo = NULL;
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
	LeaveCriticalSection(&m_critPicture);
	return bRet;
}

void CProcessInfo::clearUpUser()
{
	EnterCriticalSection(&m_critPicture);
	m_upUserInfoArr.clear();
	LeaveCriticalSection(&m_critPicture);
}

void CProcessInfo::setShowPictures()
{
	CUpUserInfo* pUpUserInfo = NULL;
	int useIndex = 1;

	EnterCriticalSection(&m_critPicture);
	int nSize = (int)m_upUserInfoArr.size();
	CRect rect = m_DrawRect;

	int nWidth = (int)(rect.Width()*0.25);

	if (nSize > 1 && nSize <= 4)
	{
		rect.bottom = m_DrawRect.bottom - (long)(m_DrawRect.Width()*0.25);
	}
	else if (nSize > 4)
	{
		rect.bottom = m_DrawRect.bottom - (long)(m_DrawRect.Width()*0.5);
	}
	for (int i = 0; i < nSize; i++)
	{
		if (m_configArr[m_upUserInfoArr[i]->m_upid] == 2)
		{
			m_upUserInfoArr[i]->m_pPictureControl = m_pPictureControlArr[0];
			m_upUserInfoArr[i]->m_pPictureControl->m_upId = 0;
			m_upUserInfoArr[i]->m_bBigPic = true;
			m_upUserInfoArr[i]->m_nTimes = 0;
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
				smallRect.top = rect.bottom + (long)(useIndex / 4 * m_DrawRect.Height()*0.25f);
			}
			smallRect.right = smallRect.left + nWidth;
			smallRect.bottom = smallRect.top + (long)(m_DrawRect.Height()*0.25);

			m_upUserInfoArr[i]->m_bBigPic = false;
			m_upUserInfoArr[i]->m_pPictureControl = m_pPictureControlArr[useIndex];
			m_upUserInfoArr[i]->m_pPictureControl->m_upId = m_upUserInfoArr[i]->m_upid;
			useIndex++;
			m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(smallRect);
			m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);
		}
	}
	LeaveCriticalSection(&m_critPicture);
}
bool CProcessInfo::sendMessage(CString winName, CString strData)
{
	bool bRet = false;
	LRESULT copyDataResult;  //copyDataResult has value returned by other app 
	CWnd *pOtherWnd = CWnd::FindWindow(NULL, winName);
	if (pOtherWnd)
	{
		COPYDATASTRUCT cpd;
		cpd.dwData = 0;
		cpd.cbData = strData.GetLength() + sizeof(wchar_t);             //data length
		cpd.lpData = (void*)strData.GetBuffer(cpd.cbData); //data buffer
		copyDataResult = pOtherWnd->SendMessage(WM_COPYDATA, (WPARAM)AfxGetApp()->m_pMainWnd->GetSafeHwnd(), (LPARAM)&cpd);
		strData.ReleaseBuffer();
		bRet = true;
	}
	return bRet;
}
void CProcessInfo::setStreamConfig()
{
	CString str;
	str.Format("%d", (int)PARENT_PROCESS_SET_STREAM_CONFIG);
	string strMessage = "{\"type\":";
	strMessage += str;
	strMessage += ",\"config\":\"";


	for (int i = 0; i < UPID_MAX_SIZE; i++)
	{
		str.Format("%d", m_configArr[i]);
		strMessage += str;
		if (i == UPID_MAX_SIZE - 1)
		{
			break;
		}
		strMessage += ",";
	}
	strMessage += "\"}";
	bool bSend = sendMessage(m_strWindowName.c_str(), strMessage.c_str());
	if (!bSend)
	{
		AfxMessageBox("send set config request failed!");
	}
}

void CProcessInfo::liveExit()
{
	if (m_bInit)
	{
		removeAllUpUser();
		EnterCriticalSection(&m_critPicture);
		m_pPictureControlArr[0]->MoveWindow(m_DrawRect);
		m_pPictureControlArr[0]->ShowWindow(SW_SHOW);
		drawBackground(m_pPictureControlArr[0]);
		LeaveCriticalSection(&m_critPicture);
		//m_bInit = false;
	}
}



void CProcessInfo::drawPic(int upid, int w, int h, uint8_t* videoData, int videoDataLen)
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

				CUtil::yuv420p_to_rgb24(videoData, videoDataRGB, w, h);

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

				float widthTextureEdge = 0.0f;
				float heightTextureEdge = 0.0f;

				float widthEdge = 0.0f;
				float heightEdge = 0.0f;

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
				if (pUpUserInfo->m_bBigPic && m_bStartFindFace)
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
						rect1.left = (long)(m_vFindFaceResult[i].pos[0] * rectScale + widthEdge);
						rect1.top = (long)(m_vFindFaceResult[i].pos[1] * rectScale + heightEdge);
						rect1.right = rect1.left + (long)((m_vFindFaceResult[i].pos[2] - m_vFindFaceResult[i].pos[0])*rectScale);
						rect1.bottom = (long)((m_vFindFaceResult[i].pos[3] - m_vFindFaceResult[i].pos[1])*rectScale) + rect1.top;

						MemDC.Rectangle(rect1);
						MemDC.TextOut(rect1.left, rect1.top - 10, m_vFindFaceResult[i].name.c_str());
					}
					LeaveCriticalSection(&m_critFaceFeature);
					MemDC.SelectObject(pOldPen);
					MemDC.SelectObject(pOldBrush);
				}


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
		printf("err");
	}

}

void CProcessInfo::drawBackground(CStatic* pPicture)
{
	try
	{
		CRect rect;
		pPicture->GetClientRect(&rect);
		CDC* pDC = pPicture->GetWindowDC();    //获得显示控件的DC
		pDC->SetStretchBltMode(COLORONCOLOR);
		FillRect(pDC->m_hDC, &rect, CBrush(RGB(0, 0, 0)));
		pPicture->ReleaseDC(pDC);
	}
	catch (char *str)
	{
		printf("err");
	}

}
