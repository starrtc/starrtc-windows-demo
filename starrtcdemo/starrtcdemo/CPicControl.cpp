#include "stdafx.h"
#include "CPicControl.h"
#include "Resource.h"

CPicControl::CPicControl()
{
	m_upId = -1;
}


CPicControl::~CPicControl()
{
	m_upId = -1;
}
BEGIN_MESSAGE_MAP(CPicControl, CStatic)
	ON_CONTROL_REFLECT(STN_DBLCLK, &CPicControl::OnStnDblclick)
	ON_COMMAND(ID_MENU_CLOSE_LOOK_LIVE, &CPicControl::OnMenuCloseLookLive)
	//	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_START_FACE_FEATURE, &CPicControl::OnMenuStartFaceFeature)
	ON_COMMAND(ID_STOP_FACE_FEATURE, &CPicControl::OnStopFaceFeature)
END_MESSAGE_MAP()

void CPicControl::setInfo(CPicControlCallback* pPicControlCallback, void* pParam)
{
	m_pPicControlCallback = pPicControlCallback;
	m_pParam = pParam;
}
void CPicControl::OnStnDblclick()
{
	if (m_pPicControlCallback != NULL)
	{
		m_pPicControlCallback->changeStreamConfig(m_pParam, m_upId);
	}
}


void CPicControl::OnMenuCloseLookLive()
{
	if (m_pPicControlCallback != NULL)
	{
		m_pPicControlCallback->closeCurrentLive(m_pParam);
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
	if (m_pPicControlCallback != NULL)
	{
		m_pPicControlCallback->startFaceFeature(m_pParam);
	}
}


void CPicControl::OnStopFaceFeature()
{
	if (m_pPicControlCallback != NULL)
	{
		m_pPicControlCallback->stopFaceFeature(m_pParam);
	}
}
