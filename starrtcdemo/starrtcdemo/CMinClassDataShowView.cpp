#include "stdafx.h"
#include "CMinClassDataShowView.h"


CMinClassDataShowView::CMinClassDataShowView()
{
}


CMinClassDataShowView::~CMinClassDataShowView()
{
}

void CMinClassDataShowView::setShowPictures()
{
	CUpUserInfo* pUpUserInfo = NULL;
	int useIndex = 1;
	EnterCriticalSection(&m_critPicture);
	int nSize = (int)m_upUserInfoArr.size();
	CRect rect = m_DrawRect;

	int nHeight = (int)(rect.Height()*0.25f);
	if (nSize > 4)
	{
		nHeight = (int)(rect.Height()/ (float)nSize);
	}

	for (int i = 0; i < nSize; i++)
	{
		CRect smallRect;
		smallRect.left = rect.left;
		smallRect.top = rect.top + i *nHeight;
		smallRect.right = rect.right;
		smallRect.bottom = smallRect.top + nHeight;
		m_upUserInfoArr[i]->m_showRect = smallRect;
		m_upUserInfoArr[i]->m_pPictureControl->MoveWindow(smallRect);
		m_upUserInfoArr[i]->m_pPictureControl->ShowWindow(SW_SHOW);

	}
	LeaveCriticalSection(&m_critPicture);
}
