#pragma once

#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif

#include "CChatManager.h"
#include "IChatManagerListener.h"
/*
 *一对一聊天管理类
 */
class MATH_API XHChatManager
{
public:
	/*
	 * 构造函数
	 * @param pUserManager 用户信息
	 * @param pListener 回调函数指针
	 */
	XHChatManager(IChatManagerListener* pListener);
	/*
	 * 析构函数
	 */
	virtual ~XHChatManager();

	/*
	 * 发送消息
	 * @param toUserId 对方userId
	 * @param msgStr 消息内容
	 * @return 消息内容
	 */
	CIMMessage* sendMessage(char* toUserId, char* msgStr);

	/*
	 * 发送在线消息
	 * @param toUserId 对方userId
	 * @param msgStr 消息内容
	 * @return 是否成功
	 */
	bool sendOnlineMessage(char* toUserId, char* msgStr);
private:
	CChatManager* m_pChatManager;
};

