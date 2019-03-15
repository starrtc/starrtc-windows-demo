#pragma once

#include "CUserManager.h"
enum LIVE_TYPE
{
	LIVE_TYPE_VDN,
	LIVE_TYPE_SRC
};
class ILiveInterface
{
public:
	ILiveInterface(CUserManager* pUserManager);
	virtual ~ILiveInterface();

	void setChannelId(string strChannelId);

	void resetReturnVal();

	/**
	 * 成功
	 * @param data
	 */
	virtual void success();

	/**
	 * 失败
	 * @param errMsg
	 */
	virtual void failed(string errMsg);

	string getChannelId();
	/*
	 * 设置数据流配置
	 */
	virtual bool setStreamConfig(int* sendBuf, int length) = 0;
public:
	LIVE_TYPE m_liveType;
protected:
	CUserManager* m_pUserManager;
	string m_ChannelId;

	bool m_bReturn;
	bool m_bSuccess;
	string m_strErrInfo;
	
};

