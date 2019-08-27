#pragma once

#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif

#include<string>
using namespace std;
#include "ILoginListener.h"
#include "CUserManager.h"
class MATH_API CLogin :public ILoginListener
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
public:
	/**
	 * msgServer错误,这个函数是新线程调用
	 */
	virtual int msgErr(char* errString);

	/**
	 * 重试多次后仍不能连接到msgServer，或用户主动调用stop后回调
	 */
	virtual int stop();

	/**
	 * msgServer处于在线状态
	 */
	virtual int online(int maxContentLen);

	/**
	 * msgServer中断状态
	 */
	virtual int offline();
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

