#pragma once

enum LIVE_VIDEO_LIST_REPORT_NAME
{
	LIVE_VIDEO_NAME = 0,
	LIVE_VIDEO_STATUS,
	LIVE_VIDEO_ID,
	LIVE_VIDEO_CREATER
};

class CLiveProgram
{
public:
	CLiveProgram();
	~CLiveProgram();

public:
	CString m_strId;
	CString m_strName;
	CString m_strCreator;
	BOOL m_liveState;
};

