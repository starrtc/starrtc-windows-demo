#pragma once
#include "CIMMessage.h"

class IStarIMC2CListener
{
public:
	virtual void onNewMessage(CIMMessage* var1) = 0;
	virtual void onSendMessageSuccess(int msgIndex) = 0;
	virtual void onSendMessageFailed(int msgIndex) = 0;
};

