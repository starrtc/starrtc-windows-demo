#pragma once
#include "CIMMessage.h"
class IChatManagerListener
{
public:
	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceiveMessage(CIMMessage* pMessage) = 0;
};

