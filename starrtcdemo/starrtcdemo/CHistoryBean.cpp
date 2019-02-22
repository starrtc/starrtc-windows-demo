#include "stdafx.h"
#include "CHistoryBean.h"


CHistoryBean::CHistoryBean()
{
	m_nId = 0;
	m_strType = "";
	m_strConversationId = "";
	m_nNewMsgCount = 0;
	m_strLastMsg = "";
	m_strLastTime = "";
	m_strGroupName = "";
	m_strGroupCreaterId = "";
}


CHistoryBean::~CHistoryBean()
{
}

int CHistoryBean::getId() {
	return m_nId;
}

void CHistoryBean::setId(int id) {
	m_nId = id;
}

string CHistoryBean::getType() {
	return m_strType;
}

void CHistoryBean::setType(string type) {
	m_strType = type;
}

string CHistoryBean::getConversationId() {
	return m_strConversationId;
}

void CHistoryBean::setConversationId(string conversationId) {
	m_strConversationId = conversationId;
}

string CHistoryBean::getLastMsg() {
	return m_strLastMsg;
}

void CHistoryBean::setLastMsg(string lastMsg) {
	m_strLastMsg = lastMsg;
}

int CHistoryBean::getNewMsgCount() {
	return m_nNewMsgCount;
}

void CHistoryBean::setNewMsgCount(int newMsgCount) {
	m_nNewMsgCount = newMsgCount;
}


string CHistoryBean::getLastTime() {
	return m_strLastTime;
}

void CHistoryBean::setLastTime(string lastTime) {
	m_strLastTime = lastTime;
}

string CHistoryBean::getGroupName() {
	return m_strGroupName;
}

void CHistoryBean::setGroupName(string groupName) {
	m_strGroupName = groupName;
}

string CHistoryBean::getGroupCreaterId()
{
	return m_strGroupCreaterId;
}

void CHistoryBean::setGroupCreaterId(string groupCreaterId)
{
	m_strGroupCreaterId = groupCreaterId;
}
