#include "stdafx.h"
#include "CSqliteDB.h"


CSqliteDB::CSqliteDB()
{
	m_pDB = NULL;
	m_strHistoryTableName = "history";
	m_strMsgTableName = "msg";
}


CSqliteDB::~CSqliteDB()
{
	closeDB();
}

bool CSqliteDB::openDB(string strDBName)
{
	bool bRet = false;
	int rc = SQLITE_ERROR;

	//打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
	rc = sqlite3_open(strDBName.c_str(), &m_pDB);
	if (rc == SQLITE_OK)
	{
		bRet = true;
		createHistoryTable();
		createMsgTable();
	}
	return bRet;
}

bool CSqliteDB::closeDB()
{
	if (m_pDB != NULL)
	{
		//打开指定的数据库文件,如果不存在将创建一个同名的数据库文件
		sqlite3_close(m_pDB);
		m_pDB = NULL;
	}
	return true;
}

int CSqliteDB::callback(void *data, int argc, char **argv, char **azColName)
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

bool CSqliteDB::createHistoryTable()
{
	char *zErrMsg = NULL;
	string strSQL = "create table if not exists " + m_strHistoryTableName + "(" +
		"id INTEGER PRIMARY KEY," +
		"type TEXT," +
		"conversationId TEXT," +
		"newMsg INTEGER," +
		"groupName TEXT," +
		"groupCreaterId TEXT," +
		"lastMsg TEXT," +
		"lastTime TEXT)";

	sqlite3_exec(m_pDB, strSQL.c_str(), 0, 0, &zErrMsg);
	return true;
}

bool CSqliteDB::createMsgTable()
{
	char *zErrMsg = NULL;
	string strSQL = "create table if not exists " + m_strMsgTableName + "(" +
		"id INTEGER PRIMARY KEY," +
		"conversationId TEXT," +
		"fromId TEXT," +
		"atId TEXT," +
		"msg TEXT," +
		"time TEXT)";
	sqlite3_exec(m_pDB, strSQL.c_str(), 0, 0, &zErrMsg);
	return true;
}

list<CHistoryBean*> CSqliteDB::getHistory(string type)
{
	sqlite3_stmt * stmt = NULL;
	list<CHistoryBean*> retList;
	string sql = "select id,conversationId,newMsg,lastMsg,lastTime,groupName,groupCreaterId from " + m_strHistoryTableName + " where type=? order by id desc";
	int result = sqlite3_prepare_v2(m_pDB, sql.c_str(), -1, &stmt, 0);

	if (result == SQLITE_OK)
	{
		int nColCount = sqlite3_column_count(stmt);

		CString strtype = type.c_str();
		sqlite3_bind_text(stmt, 1, strtype.GetBuffer(0), -1, SQLITE_STATIC);
		
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			CHistoryBean* pHistoryBean = new CHistoryBean();
			int nId = sqlite3_column_int(stmt, 0);
			pHistoryBean->setId(nId);
			CString str = "";
			str.Format("%s", sqlite3_column_text(stmt, 1));
			pHistoryBean->setConversationId(str.GetBuffer(0));

			pHistoryBean->setNewMsgCount(sqlite3_column_int(stmt, 2));

			str.Format("%s", sqlite3_column_text(stmt, 3));
			pHistoryBean->setLastMsg(str.GetBuffer(0));

			str.Format("%s", sqlite3_column_text(stmt, 4));
			pHistoryBean->setLastTime(str.GetBuffer(0));

			str.Format("%s", sqlite3_column_text(stmt, 5));
			pHistoryBean->setGroupName(str.GetBuffer(0));

			str.Format("%s", sqlite3_column_text(stmt, 6));
			pHistoryBean->setGroupCreaterId(str.GetBuffer(0));
			retList.push_back(pHistoryBean);
		}
	}
	return retList;
}

bool CSqliteDB::setHistory(CHistoryBean* pHistoryBean, bool hasRead)
{
	bool bRet = false;
	if (pHistoryBean->getConversationId() == "" || pHistoryBean->getType() == "")
	{
		return bRet;
	}

	sqlite3_stmt * stmt = NULL;

	string sql = "select id,newMsg from " + m_strHistoryTableName + " where type=? and conversationId=?";
	int result = sqlite3_prepare_v2(m_pDB, sql.c_str(), -1, &stmt, 0);

	if (result == SQLITE_OK)
	{
		CString strType = pHistoryBean->getType().c_str();
		sqlite3_bind_text(stmt, 1, strType.GetBuffer(0), -1, SQLITE_STATIC);
		CString strConversationId = pHistoryBean->getConversationId().c_str();
		sqlite3_bind_text(stmt, 2, strConversationId.GetBuffer(0), -1, SQLITE_STATIC);
		if (sqlite3_step(stmt) == SQLITE_ROW) 
		{
			int nId = sqlite3_column_int(stmt, 0);
			int nMsgCount = 0;
			if (!hasRead)
			{
				nMsgCount = sqlite3_column_int(stmt, 1)+1;
			}
			pHistoryBean->setId(nId);
			pHistoryBean->setNewMsgCount(nMsgCount);
			sqlite3_finalize(stmt); //关闭连接，避免
			stmt = NULL;

			sql = "UPDATE " + m_strHistoryTableName + " SET newMsg = ?," +
				" lastMsg = ?," +
				" lastTime = ?" +
				" where type=? and conversationId=?";
			int result = sqlite3_prepare_v2(m_pDB, sql.c_str(), -1, &stmt, 0);
			if (result == SQLITE_OK)
			{
				sqlite3_bind_int(stmt, 1, pHistoryBean->getNewMsgCount());
				CString strLastMsg = pHistoryBean->getLastMsg().c_str();
				sqlite3_bind_text(stmt, 2, strLastMsg.GetBuffer(0), -1, SQLITE_STATIC);
				CString strLastTime = pHistoryBean->getLastTime().c_str();
				sqlite3_bind_text(stmt, 3, strLastTime.GetBuffer(0), -1, SQLITE_STATIC);

				sqlite3_bind_text(stmt, 4, strType.GetBuffer(0), -1, SQLITE_STATIC);

				sqlite3_bind_text(stmt, 5, strConversationId.GetBuffer(0), -1, SQLITE_STATIC);
				if (sqlite3_step(stmt) == SQLITE_ROW)
				{
					bRet = true;
				}
				sqlite3_finalize(stmt); //关闭连接，避免
				stmt = NULL;
			}
			
		}
		else
		{
			sqlite3_finalize(stmt); //关闭连接，避免
			stmt = NULL;

			sql = "insert into " + m_strHistoryTableName + "(type,conversationId,newMsg,lastMsg,lastTime,groupName,groupCreaterId) values(?,?,?,?,?,?,?)";
			int result = sqlite3_prepare_v2(m_pDB, sql.c_str(), -1, &stmt, 0);
			if (result == SQLITE_OK)
			{
				sqlite3_bind_text(stmt, 1, strType.GetBuffer(0), -1, SQLITE_STATIC);

				sqlite3_bind_text(stmt, 2, strConversationId.GetBuffer(0), -1, SQLITE_STATIC);

				sqlite3_bind_int(stmt, 3, pHistoryBean->getNewMsgCount());

				CString strLastMsg = pHistoryBean->getLastMsg().c_str();
				sqlite3_bind_text(stmt, 4, strLastMsg.GetBuffer(0), -1, SQLITE_STATIC);

				CString strLastTime = pHistoryBean->getLastTime().c_str();
				sqlite3_bind_text(stmt, 5, strLastTime.GetBuffer(0) , -1, SQLITE_STATIC);

				CString strGroupName = pHistoryBean->getGroupName().c_str();
				sqlite3_bind_text(stmt, 6, strGroupName.GetBuffer(0), -1, SQLITE_STATIC);

				CString strGroupCreaterId = pHistoryBean->getGroupCreaterId().c_str();
				sqlite3_bind_text(stmt, 7, strGroupCreaterId.GetBuffer(0), -1, SQLITE_STATIC);

				if (sqlite3_step(stmt) == SQLITE_ROW)
				{
					bRet = true;
				}
				sqlite3_finalize(stmt); //关闭连接，避免
				stmt = NULL;
			}
		}
	}

	if (stmt != NULL)
	{
		sqlite3_finalize(stmt); //关闭连接，避免
		stmt = NULL;
	}
	

	return bRet;
}

list<CMessageBean*> CSqliteDB::getMessageList(string conversationId)
{
	sqlite3_stmt * stmt = NULL;
	list<CMessageBean*> retList;
	string sql = "select id,conversationId,fromId,msg,time from " + m_strMsgTableName + " where conversationId = ? or fromId = ? order by id desc limit 5";
	int result = sqlite3_prepare_v2(m_pDB, sql.c_str(), -1, &stmt, 0);

	if (result == SQLITE_OK)
	{
		int nColCount = sqlite3_column_count(stmt);
		CString strConversationId = conversationId.c_str();
		sqlite3_bind_text(stmt, 1, strConversationId.GetBuffer(0), -1, SQLITE_STATIC);

		sqlite3_bind_text(stmt, 2, strConversationId.GetBuffer(0), -1, SQLITE_STATIC);

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			CMessageBean* pMessageBean = new CMessageBean();
			int nId = sqlite3_column_int(stmt, 0);
			pMessageBean->setId(nId);
			CString str = "";
			str.Format("%s", sqlite3_column_text(stmt, 1));
			pMessageBean->setConversationId(str.GetBuffer(0));

			str.Format("%s", sqlite3_column_text(stmt, 2));
			pMessageBean->setFromId(str.GetBuffer(0));


			str.Format("%s", sqlite3_column_text(stmt, 3));
			pMessageBean->setMsg(str.GetBuffer(0));

			str.Format("%s", sqlite3_column_text(stmt, 4));
			pMessageBean->setTime(str.GetBuffer(0));
			retList.push_back(pMessageBean);
		}
	}
	return retList;
}

bool CSqliteDB::setMessage(CMessageBean* pMsgBean)
{
	bool bRet = false;
	sqlite3_stmt * stmt = NULL;

	string sql = "insert into " + m_strMsgTableName + " (conversationId,fromId,msg,time) values(?,?,?,?)";
	int result = sqlite3_prepare_v2(m_pDB, sql.c_str(), -1, &stmt, 0);

	if (result == SQLITE_OK)
	{
		CString strConversationId = pMsgBean->getConversationId().c_str();
		sqlite3_bind_text(stmt, 1, strConversationId.GetBuffer(0), -1, SQLITE_STATIC);

		CString strFromId = pMsgBean->getFromId().c_str();
		sqlite3_bind_text(stmt, 2, strFromId.GetBuffer(0), -1, SQLITE_STATIC);

		CString strMsg = pMsgBean->getMsg().c_str();
		sqlite3_bind_text(stmt, 3, strMsg.GetBuffer(0), -1, SQLITE_STATIC);

		CString strTime = pMsgBean->getTime().c_str();
		sqlite3_bind_text(stmt, 4, strTime.GetBuffer(0), -1, SQLITE_STATIC);

		if (sqlite3_step(stmt) == SQLITE_ROW)
		{
			bRet = true;
		}
	}
	if (stmt != NULL)
	{
		sqlite3_finalize(stmt); //关闭连接，避免
		stmt = NULL;
	}
	return bRet;
}
