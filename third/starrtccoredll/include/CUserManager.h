#pragma once
#include<string>
using namespace std;
#include "CServiceParam.h"

class CUserManager
{

public:
	string m_strAuthKey;
	string  m_strTokenId;

	string m_strIMServerIp;
	int m_nIMServerPort;
	bool m_bUserDispatch;

	CServiceParam m_ServiceParam;

};

