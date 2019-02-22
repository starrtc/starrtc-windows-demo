#pragma once

#include "CUserManager.h"
class ILiveInterface
{
public:
	ILiveInterface(CUserManager* pUserManager);
	virtual ~ILiveInterface();

	void setChannelId(string strChannelId);

	/*
	 * 设置数据流配置
	 */
	bool setStreamConfig(int* sendBuf, int length);

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
protected:
	CUserManager* m_pUserManager;
	string m_ChannelId;

	bool m_bReturn;
	bool m_bSuccess;
	string m_strErrInfo;
};

