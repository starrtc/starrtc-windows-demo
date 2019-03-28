#pragma once
#include "CIMMessage.h"

class IChatroomManagerListener 
{
public:
	/**
	 * 聊天室成员数变化
	 * @param number
	 */
	virtual void onMembersUpdated(int number) = 0;

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfKicked() = 0;

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfMuted(int seconds) = 0;

	/**
	 * 聊天室已关闭
	 */
	virtual void onClosed() = 0;

	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(CIMMessage* pMessage) = 0;

	/**
	 * 收到私信消息
	 * @param message
	 */
	virtual void onReceivePrivateMessage(CIMMessage* pMessage) = 0;
};