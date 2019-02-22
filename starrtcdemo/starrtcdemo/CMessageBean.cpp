#include "stdafx.h"
#include "CMessageBean.h"


CMessageBean::CMessageBean()
{
	m_nId = 0;
	m_strConversationId = "";
	m_strFromId = "";
	m_strMsg = "";
	m_strTime = "";
}


CMessageBean::~CMessageBean()
{
}

int CMessageBean::getId()
{
	return m_nId;
}

void CMessageBean::setId(int id) 
{
	m_nId = id;
}

string CMessageBean::getConversationId() 
{
	return m_strConversationId;
}

void CMessageBean::setConversationId(string conversationId) 
{
	m_strConversationId = conversationId;
}

string CMessageBean::getFromId() 
{
	return m_strFromId;
}

void CMessageBean::setFromId(string fromId) 
{
	m_strFromId = fromId;
}

string CMessageBean::getMsg() 
{
	return m_strMsg;
}

void CMessageBean::setMsg(string msg)
{
	m_strMsg = msg;
}

string CMessageBean::getTime()
{
	return m_strTime;
}

void CMessageBean::setTime(string lastTime)
{
	m_strTime = lastTime;
}
