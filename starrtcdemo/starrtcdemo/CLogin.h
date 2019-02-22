#pragma once
#include<string>
using namespace std;
#include "CUserManager.h"
class CLogin
{
public:
	CLogin(CUserManager* pUserManager);

	~CLogin();

	bool readConfig();
	bool writeConfig();
	string getServiceParam();

	/*
	 * 登录
	 */
	bool logIn();

	/*
	 * 获取authKey
	 */
	bool getAuthKey(string userId);

	/*
	 * 获取Token
	 */
	bool getToken(string userId, string agentId, string authKey);

	/*
	 * 通过调度获取IM服务地址
	 */
	bool getIMServerAddr(string userId, string agentId);

	/*
	 * 开启IM服务
	 */
	bool startIMServer(string strIP, int nPort, string userId, string agentId, string strToken);

	/*
	 * 开启IM服务
	 */
	bool stopIMServer();

	/*
	 * 开启IM服务
	 */
	string getUserManagerInfo();
private:
	CUserManager* m_pUserManager;
};

