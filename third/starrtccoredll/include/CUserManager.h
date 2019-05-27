#pragma once
#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif

#include<string>
using namespace std;
#include "CServiceParam.h"

#define AUDIO_SAMPLE_RATE	16000
#define AUDIO_CHANNELS		1
#define AUDIO_BIT_RATE		32
class CAudioParam
{
public:
	int m_nSampleRateInHz;
	int m_nChannels;
	int m_nBitRate;
};

class MATH_API CUserManager
{
public:
	CUserManager();
	~CUserManager();
	bool readConfig();
	bool writeConfig();
	string getServiceParam();
	string getUserManagerInfo();
public:
	string m_strAuthKey;
	string  m_strTokenId;

	string m_strIMServerIp;
	int m_nIMServerPort;
	bool m_bUserDispatch;
	bool m_bVoipP2P;
	CServiceParam m_ServiceParam;
	CAudioParam m_AudioParam;
	
};

