#pragma once
#include<string>
using namespace std;

class CResolutionRatio
{
public:
	int m_nWidth;
	int m_nHeight;
};
class CServiceParam
{

public:
	string  m_strUserId;
	string  m_strAgentId;

	string  m_strLoginServiceIP;
	string  m_strMessageServiceIP;
	string  m_strChatServiceIP;
	string  m_strUploadServiceIP;
	string  m_strDownloadServiceIP;
	string  m_strVOIPServiceIP;

	string  m_strRequestListAddr;

public:
	CResolutionRatio m_BigPic;
	CResolutionRatio m_SmallPic;

};

