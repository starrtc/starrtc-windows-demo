#pragma once
#include <afxwin.h>
#include "CPicControlCallback.h"
class CPicControl :
	public CStatic
{
public:
	CPicControl();
	virtual ~CPicControl();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnStnDblclick();
public:
	void setInfo(CPicControlCallback* pPicControlCallback, void* pParam);
public:
	int m_upId;
	void* m_pParam;
	CPicControlCallback* m_pPicControlCallback;
	afx_msg void OnMenuCloseLookLive();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuStartFaceFeature();
	afx_msg void OnStopFaceFeature();
};

