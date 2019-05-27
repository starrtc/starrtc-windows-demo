#include "stdafx.h"
#include "CVoipDataShowView.h"


CVoipDataShowView::CVoipDataShowView()
{
}


CVoipDataShowView::~CVoipDataShowView()
{
}

void CVoipDataShowView::setShowPictures()
{
	/*CUpUserInfo* pUpUserInfo = NULL;
	int useIndex = 1;

	EnterCriticalSection(&m_critPicture);
	int nSize = (int)m_upUserInfoArr.size();

	CRect rectLeft = m_DrawRect;
	rectLeft.right = m_DrawRect.left + (int)(m_DrawRect.Width()*0.5f) - 5;
	CRect rectRight = m_DrawRect;
	rectRight.left = rectLeft.right + 10;
	for (int i = 0; i < 2; i++)
	{
		if (m_configArr[m_upUserInfoArr[i]->m_upid] == 2)
		{
			m_upUserInfoArr[i]->m_pPictureControl = m_pPictureControlArr[0];
			m_upUserInfoArr[i]->m_pPictureControl->m_upId = 0;
			m_upUserInfoArr[i]->m_bBigPic = true;
			m_upUserInfoArr[i]->m_nTimes = 0;
			m_upUserInfoArr[i]->m_showRect = rectLeft;
			m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(rectLeft);
			m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);

		}
		else
		{
			m_upUserInfoArr[i]->m_bBigPic = false;
			m_upUserInfoArr[i]->m_pPictureControl = m_pPictureControlArr[1];
			m_upUserInfoArr[i]->m_pPictureControl->m_upId = m_upUserInfoArr[i]->m_upid;
			m_upUserInfoArr[i]->m_showRect = rectRight;
			m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(rectRight);
			m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);
		}
	}
	LeaveCriticalSection(&m_critPicture);*/
}


