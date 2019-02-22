#pragma once
#include <string>
using namespace std;

class CMessageBean
{
public:
	CMessageBean();
	virtual ~CMessageBean();
	int getId();
	void setId(int id);
	string getConversationId();
	void setConversationId(string conversationId);
	string getFromId();
	void setFromId(string fromId);
	string getMsg();
	void setMsg(string msg);
	string getTime();
	void setTime(string lastTime);
private:
	int m_nId;
	string m_strConversationId;
	string m_strFromId;
	string m_strMsg;
	string m_strTime;
};

