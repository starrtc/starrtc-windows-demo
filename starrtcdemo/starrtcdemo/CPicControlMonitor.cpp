#include "stdafx.h"
#include "CPicControlMonitor.h"
#include "Resource.h"

CPicControlMonitor::CPicControlMonitor()
{
	m_strUserId = "";
	m_bIsBig = false;
}

CPicControlMonitor::~CPicControlMonitor()
{
	m_strUserId = "";
	m_bIsBig = false;
}
BEGIN_MESSAGE_MAP(CPicControlMonitor, CStatic)
	ON_CONTROL_REFLECT(STN_DBLCLK, &CPicControlMonitor::OnStnDblclick)
	ON_COMMAND(ID_MENU_CLOSE_LOOK_LIVE, &CPicControlMonitor::OnMenuCloseLookLive)
	//	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_START_FACE_FEATURE, &CPicControlMonitor::OnMenuStartFaceFeature)
	ON_COMMAND(ID_STOP_FACE_FEATURE, &CPicControlMonitor::OnStopFaceFeature)
END_MESSAGE_MAP()

void CPicControlMonitor::setInfo(CPicControlMonitorCallback* pPicControlCallback, void* m_pParam)
{
	m_pPicControlCallback = pPicControlCallback;
}

void CPicControlMonitor::OnStnDblclick()
{

}

void CPicControlMonitor::OnMenuCloseLookLive()
{
	if (m_pPicControlCallback != NULL)
	{
		m_pPicControlCallback->closeCurrentLive(m_pParam);
	}
}

void CPicControlMonitor::OnRButtonDown(UINT nFlags, CPoint point)
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

void CPicControlMonitor::OnMenuStartFaceFeature()
{
	if (m_pPicControlCallback != NULL)
	{
		m_pPicControlCallback->startFaceFeature(m_pParam);
	}
}

void CPicControlMonitor::OnStopFaceFeature()
{
	if (m_pPicControlCallback != NULL)
	{
		m_pPicControlCallback->stopFaceFeature(m_pParam);
	}
}
