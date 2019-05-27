#pragma once
#include<string>
using namespace std;
class CCallbackResult
{
public:
	CCallbackResult();
	~CCallbackResult();
	void reset();
public:
	bool m_bResult;
	bool m_bSuccess;
	int m_errorCode;
	string m_strErr;
};

