#pragma once
#include "CIMMessage.h"
class IMeetingManagerListener
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

	virtual int uploaderAdd(char* upUserId, int upId) = 0;
	virtual int uploaderRemove(char* upUserId, int upId) = 0;
	virtual int getRealtimeData(int upId, uint8_t* data, int len) = 0;
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;

	//src
	virtual int deleteChannel(char* channelId) = 0;
	virtual int stopOK() = 0;
	virtual int srcError(char* errString) = 0;
};