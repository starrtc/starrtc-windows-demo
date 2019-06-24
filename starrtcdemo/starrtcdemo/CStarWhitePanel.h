#pragma once
#include <afxwin.h>


class CStarWhitePanel :
	public CStatic
{
public:
	CStarWhitePanel();
	~CStarWhitePanel();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnPaint();
public:
	//打开激光笔
	void laserPenOn();
	//关闭激光笔
	void laserPenOff();

private:
	bool m_bDraw;
	bool m_bLaserOn;
	CPoint m_StartPoint;
};

