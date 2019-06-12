#pragma once
#include <afxwin.h>
#include "IButtonCallback.h"
class CCustomButton :
	public CButton
{
public:
	CCustomButton();
	virtual ~CCustomButton();
	void setCallback(IButtonCallback* pCallback);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	IButtonCallback* m_pCallback;
};

