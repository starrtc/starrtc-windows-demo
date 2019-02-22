#pragma once
#include <string>
using namespace std;
class CHistoryBean
{
public:
	CHistoryBean();
	virtual ~CHistoryBean();
public:
	int getId();
	void setId(int id);
	string getType();
	void setType(string type);
	string getConversationId();
	void setConversationId(string conversationId);
	string getLastMsg();
	void setLastMsg(string lastMsg);
	int getNewMsgCount();
	void setNewMsgCount(int newMsgCount);
	string getLastTime();
	void setLastTime(string lastTime);
	string getGroupName();
	void setGroupName(string groupName);
	string getGroupCreaterId();
	void setGroupCreaterId(string groupCreaterId);
private:
	int m_nId;
	string m_strType;
	string m_strConversationId;
	int m_nNewMsgCount;
	string m_strLastMsg;
	string m_strLastTime;
	string m_strGroupName;
	string m_strGroupCreaterId;
};

