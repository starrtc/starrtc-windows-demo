#include "stdafx.h"
#include "CCustomButton.h"


CCustomButton::CCustomButton()
{
	m_pCallback = NULL;
}


CCustomButton::~CCustomButton()
{
	m_pCallback = NULL;
}
BEGIN_MESSAGE_MAP(CCustomButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()
void CCustomButton::setCallback(IButtonCallback* pCallback)
{
	m_pCallback = pCallback;
}

void CCustomButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnLButtonDown(nFlags, point);
	if (m_pCallback != NULL)
	{
		m_pCallback->OnLButtonDownCallback();
	}
}


void CCustomButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnLButtonUp(nFlags, point);
	if (m_pCallback != NULL)
	{
		m_pCallback->OnLButtonUpCallback();
	}
}
