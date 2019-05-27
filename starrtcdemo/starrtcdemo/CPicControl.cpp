#include "stdafx.h"
#include "CPicControl.h"
#include "Resource.h"

CPicControl::CPicControl()
{
	m_strUserId = "";
	m_bIsBig = false;
}


CPicControl::~CPicControl()
{
	m_strUserId = "";
	m_bIsBig = false;
}
BEGIN_MESSAGE_MAP(CPicControl, CStatic)
	ON_CONTROL_REFLECT(STN_DBLCLK, &CPicControl::OnStnDblclick)
	ON_COMMAND(ID_MENU_CLOSE_LOOK_LIVE, &CPicControl::OnMenuCloseLookLive)
	//	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_START_FACE_FEATURE, &CPicControl::OnMenuStartFaceFeature)
	ON_COMMAND(ID_STOP_FACE_FEATURE, &CPicControl::OnStopFaceFeature)
END_MESSAGE_MAP()

void CPicControl::setInfo(CPicControlCallback* pPicControlCallback)
{
	m_pPicControlCallback = pPicControlCallback;
}
void CPicControl::OnStnDblclick()
{
	if (m_pPicControlCallback != NULL)
	{
		if (!m_bIsBig)
		{
			m_pPicControlCallback->changeShowStyle(m_strUserId);
		}	
	}
}


void CPicControl::OnMenuCloseLookLive()
{
	if (m_pPicControlCallback != NULL)
	{
		m_pPicControlCallback->closeCurrentLive();
	}
}



void CPicControl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMenu menu;
	CMenu *pSubMenu;
	menu.LoadMenu(IDR_MENU1);
	pSubMenu = menu.GetSubMenu(0);
	CPoint point1;
	GetCursorPos(&point1);
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point1.x, point1.y, this);
	pSubMenu->DestroyMenu();
	menu.DestroyMenu();

	CStatic::OnRButtonDown(nFlags, point);
}


void CPicControl::OnMenuStartFaceFeature()
{

}


void CPicControl::OnStopFaceFeature()
{
	
}
