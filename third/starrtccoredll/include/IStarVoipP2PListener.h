#pragma once
#include <string>
#include "CIMMessage.h"
using namespace std;

class IStarVoipP2PListener 
{
public:
	/**
	 * 报错
	 */
	virtual void onError(string code) = 0;

	/**
	 * 已关闭
	 */
	virtual void onStop(string code) = 0;

	/**
	 * 收到实时数据
	 */
	virtual void onRevRealtimeData(uint8_t* bytes, int length) = 0;

	virtual void onP2PConnectSuccess() = 0;
	virtual void onP2PConnectFailed() = 0;

	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceiveMessage(CIMMessage* pMessage) = 0;
};