#include "stdafx.h"
#include "StarIMMessageBuilder.h"
#include "StarIMMessageType.h"
#include "CUtil.h"
int StarIMMessageBuilder::msgIndex = 0;
StarIMMessageBuilder::StarIMMessageBuilder()
{
}


StarIMMessageBuilder::~StarIMMessageBuilder()
{
}

int StarIMMessageBuilder::getMsgIndex() 
{
	return msgIndex;
}

CIMMessage* StarIMMessageBuilder::getC2CMessage(string fromId, string targetId, string data) {
	CIMMessage* pMsg = new CIMMessage();
	pMsg->m_nType = MSG_TYPE_CUSTOMER;
	pMsg->m_strContentData = data;
	pMsg->m_strFromId = fromId;
	pMsg->m_strTargetId = targetId;
	pMsg->m_Time = atoll(CUtil::getTime().c_str());
	pMsg->m_nMsgIndex = msgIndex++;
	return pMsg;
}

CIMMessage* StarIMMessageBuilder::getGhatRoomMessage(string fromId, string roomId, string data)
{
	CIMMessage* pMsg = new CIMMessage();
	pMsg->m_nType = MSG_TYPE_CUSTOMER;
	pMsg->m_strContentData = data;
	pMsg->m_strFromId = fromId;
	pMsg->m_strTargetId = roomId;
	pMsg->m_Time = CUtil::getCurrentTime();
	pMsg->m_nMsgIndex = msgIndex++;
	return pMsg;
}

CIMMessage* StarIMMessageBuilder::getGhatRoomContrlMessage(string fromId, string roomId, int code)
{
	CIMMessage* pMsg = new CIMMessage();
	pMsg->m_nType = MSG_TYPE_CONTROL;
	pMsg->m_nCode = code;
	pMsg->m_strContentData = "";
	pMsg->m_strFromId = fromId;
	pMsg->m_strTargetId = roomId;
	pMsg->m_Time = CUtil::getCurrentTime();
	pMsg->m_nMsgIndex = msgIndex++;
	return pMsg;
}

CIMMessage* StarIMMessageBuilder::getGroupMessage(string fromId, string groupId, string atUsers, string data)
{
	CIMMessage* pMsg = new CIMMessage();
	pMsg->m_nType = MSG_TYPE_CUSTOMER;
	pMsg->m_strContentData = data;
	pMsg->m_strFromId = fromId;
	pMsg->m_strTargetId = groupId;
	pMsg->m_strAtList = atUsers;
	pMsg->m_Time = CUtil::getCurrentTime();
	pMsg->m_nMsgIndex = msgIndex++;
	return pMsg;
}

CIMMessage* StarIMMessageBuilder::getVoipMessage(string fromId, string targetId, int code, string data)
{
	CIMMessage* pMsg = new CIMMessage();
	pMsg->m_nType = MSG_TYPE_CONTROL;
	pMsg->m_nCode = code;
	pMsg->m_strContentData = data;
	pMsg->m_strFromId = fromId;
	pMsg->m_strTargetId = targetId;
	pMsg->m_Time = CUtil::getCurrentTime();
	pMsg->m_nMsgIndex = msgIndex++;
	return pMsg;
}
