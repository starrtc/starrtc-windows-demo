#pragma once
#include "CIMMessage.h"
class StarIMMessageBuilder
{
public:
	StarIMMessageBuilder();
	virtual ~StarIMMessageBuilder();
public:
	static int getMsgIndex();
	static CIMMessage* getC2CMessage(string fromId, string targetId, string data);
	static CIMMessage* getGhatRoomMessage(string fromId, string roomId, string data);
	static CIMMessage* getGhatRoomContrlMessage(string fromId, string roomId, int code);
	static CIMMessage* getGroupMessage(string fromId, string groupId, string atUsers, string data);
	static CIMMessage* getVoipMessage(string fromId, string targetId, int code, string data);
	static CIMMessage* getVoipP2PMessage(string fromId, string targetId, int code, string data);

private:
	static int msgIndex;

};

