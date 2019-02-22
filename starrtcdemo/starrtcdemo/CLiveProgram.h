#pragma once
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

