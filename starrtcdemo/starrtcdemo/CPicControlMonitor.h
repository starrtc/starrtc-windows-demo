#pragma once
#include <afxwin.h>
#include <string>
#include "CPicControlMonitorCallback.h"
using namespace std;
class CPicControlMonitor :
	public CStatic
{
public:
	CPicControlMonitor();
	virtual ~CPicControlMonitor();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnStnDblclick();
public:
	void setInfo(CPicControlMonitorCallback* pPicControlCallback, void* m_pParam);
public:
	string m_strUserId;
	bool m_bIsBig;
	CPicControlMonitorCallback* m_pPicControlCallback;
	void* m_pParam;
	afx_msg void OnMenuCloseLookLive();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuStartFaceFeature();
	afx_msg void OnStopFaceFeature();
};

