#pragma once
#include "sqlite3.h"
#include <string>
#include "CHistoryBean.h"
#include "CMessageBean.h"
#include <list>
using namespace std;

#define HISTORY_TYPE_VOIP  "voip"
#define HISTORY_TYPE_C2C  "c2c"
#define HISTORY_TYPE_GROUP  "group"
class CSqliteDB
{
public:
	CSqliteDB();
	~CSqliteDB();
	bool openDB(string strDBName);
	bool closeDB();
	static int callback(void *data, int argc, char **argv, char **azColName);

	bool createHistoryTable();
	bool createMsgTable();
	list<CHistoryBean*> getHistory(string type);
	bool setHistory(CHistoryBean* pHistoryBean, bool hasRead);
	list<CMessageBean*> getMessageList(string conversationId);
	bool setMessage(CMessageBean* pMsgBean);
public:
	sqlite3 *m_pDB;
	string m_strHistoryTableName;
	string m_strMsgTableName;
};

