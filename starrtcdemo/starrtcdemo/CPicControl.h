#pragma once
#include <afxwin.h>
#include <string>
#include "CPicControlCallback.h"
using namespace std;
class CPicControl :
	public CStatic
{
public:
	CPicControl();
	virtual ~CPicControl();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnStnDblclick();
public:
	void setInfo(CPicControlCallback* pPicControlCallback);
public:
	string m_strUserId;
	bool m_bIsBig;
	CPicControlCallback* m_pPicControlCallback;
	afx_msg void OnMenuCloseLookLive();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuStartFaceFeature();
	afx_msg void OnStopFaceFeature();
};

