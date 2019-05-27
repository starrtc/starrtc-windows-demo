#pragma once

#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif

#include<string>
using namespace std;

#include "CUserManager.h"
class MATH_API CLogin
{
public:
	CLogin(CUserManager* pUserManager);

	~CLogin();
	/*
	 * 登录
	 */
	bool logIn();

	/*
	 * 开启IM服务
	 */
	bool startIMServer(string strIP, int nPort, string userId, string agentId, string strToken);

	/*
	 * 开启IM服务
	 */
	bool stopIMServer();
private:
	/*
	 * 获取authKey
	 */
	bool getAuthKey();

	/*
	 * 获取Token
	 */
	bool getToken();

	/*
	 * 通过调度获取IM服务地址
	 */
	bool getIMServerAddr();
};

