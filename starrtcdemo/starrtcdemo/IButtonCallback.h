#pragma once
class IButtonCallback
{
public:
	virtual void OnLButtonDownCallback() = 0;
	virtual void OnLButtonUpCallback() = 0;
};