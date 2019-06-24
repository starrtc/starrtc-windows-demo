#pragma once
#include "WhitePanelActionType.h"
#include "atltypes.h"
class CScreenPoint
{
public:
	double x;
	double y;
};

class CWhitePanelInfo
{
public:
	WHITE_PANEL_ACTION type;
	CScreenPoint point;
	int lineColor;
};
class IWhitePanelCallback
{
public:
	virtual void actionCallback(WHITE_PANEL_ACTION type, CScreenPoint& point, int lineColor) = 0;
};
