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
	int m_nLoginServicePort;
	string  m_strMessageServiceIP;
	int m_nMessageServicePort;
	string  m_strChatServiceIP;
	int m_nChatServicePort;
	string  m_strUploadServiceIP;
	int m_nUploadServicePort;
	string  m_strDownloadServiceIP;
	int m_nDownloadServicePort;
	string  m_strVOIPServiceIP;
	int m_nVOIPServicePort;

	string  m_strRequestListAddr;

public:
	int m_CropType;
	int m_FrameRate;
};

