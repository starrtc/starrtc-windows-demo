#include "stdafx.h"
#include "CGroupManager.h"
#include "StarIMMessageBuilder.h"
#include "HttpClient.h"
#include "json.h"
IGroupGetListListener* CGroupManager::m_pGroupGetListListener = NULL;
CGroupManager::CGroupManager(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
	m_pGroupManagerListener = NULL;
	m_pStarRtcCore = StarRtcCore::getStarRtcCoreInstance();
	m_pStarRtcCore->addGroupListener(this);
}


CGroupManager::~CGroupManager()
{
	m_pGroupManagerListener = NULL;
	m_pStarRtcCore->addGroupListener(NULL);
}

void CGroupManager::addGroupGetListListener(IGroupGetListListener* pGroupGetListListener)
{
	m_pGroupGetListListener = pGroupGetListListener;
}

void CGroupManager::getGroupList(CUserManager* pUserManager)
{
	if (pUserManager->m_bUserDispatch)
	{
		list<CGroupInfo> retGroupList;
		CString stUrl = "";
		stUrl.Format(_T("%s/group/list_all?userid=%s&appid=%s"), pUserManager->m_ServiceParam.m_strRequestListAddr.c_str(), pUserManager->m_ServiceParam.m_strUserId.c_str(), pUserManager->m_ServiceParam.m_strAgentId.c_str());

		char* data = "";

		CString strPara = _T("");
		CString strContent;

		CHttpClient httpClient;
		int nRet = httpClient.HttpPost(stUrl, strPara, strContent);

		string str_json = strContent.GetBuffer(0);
		Json::Reader reader;
		Json::Value root;
		if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素   
		{
			std::cout << "========================[Dispatch]========================" << std::endl;
			if (root.isMember("status") && root["status"].asInt() == 1)
			{
				if (root.isMember("data"))
				{
					Json::Value data = root.get("data", "");
					int nSize = data.size();
					for (int i = 0; i < nSize; i++)
					{
						CGroupInfo groupInfo;
						if (data[i].isMember("creator"))
						{
							groupInfo.m_strCreaterId = data[i]["creator"].asCString();
						}

						if (data[i].isMember("groupId"))
						{
							groupInfo.m_strId = data[i]["groupId"].asCString();
						}

						if (data[i].isMember("groupName"))
						{
							groupInfo.m_strName = data[i]["groupName"].asCString();
						}
						retGroupList.push_back(groupInfo);
					}
				}
			}
		}
		if (m_pGroupGetListListener != NULL)
		{
			m_pGroupGetListListener->applyGetGroupListFin(retGroupList);
		}	
	}
	else
	{
		StarRtcCore::getStarRtcCoreInstance()->applyGetGroupList();
	}
	
}

void CGroupManager::getUserList(CUserManager* pUserManager, string strGroupId)
{
	if (pUserManager->m_bUserDispatch)
	{
		list<string> userList;

		CString stUrl = "";
		stUrl.Format(_T("%s/group/members?groupId=%s&appid=%s"), pUserManager->m_ServiceParam.m_strRequestListAddr.c_str(), strGroupId.c_str(), pUserManager->m_ServiceParam.m_strAgentId.c_str());

		char* data = "";

		CString strPara = _T("");
		CString strContent;

		CHttpClient httpClient;
		int nRet = httpClient.HttpPost(stUrl, strPara, strContent);

		string str_json = strContent.GetBuffer(0);
		Json::Reader reader;
		Json::Value root;
		if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素   
		{
			std::cout << "========================[Dispatch]========================" << std::endl;
			if (root.isMember("status") && root["status"].asInt() == 1)
			{
				if (root.isMember("data"))
				{
					Json::Value data = root.get("data", "");
					int nSize = data.size();
					for (int i = 0; i < nSize; i++)
					{
						string str;
						if (data[i].isMember("userId"))
						{
							str = data[i]["userId"].asCString();
							userList.push_back(str);
						}
					}
				}
			}
		}
		if (m_pGroupGetListListener != NULL)
		{
			m_pGroupGetListListener->applyGetUserListFin(userList);
		}
	}
	else
	{
		StarRtcCore::getStarRtcCoreInstance()->applyGetUserList((char*)strGroupId.c_str());
	}
	
}

/**
 * 添加监听
 * @param groupManagerListener
 */
void CGroupManager::addListener(IGroupManagerListener* pGroupManagerListener)
{
	m_pGroupManagerListener = pGroupManagerListener;
}

/**
 * 创建群
 * @param groupName
 * @param callback
 */
bool CGroupManager::createGroup(string groupName)
{
	if (m_pStarRtcCore != NULL)
	{
		int nret = m_pStarRtcCore->applyCreateGroup("", (char*)groupName.c_str());
	}	
	return true;
}

/**
 * 删除群
 * @param groupID
 */
bool CGroupManager::deleteGroup(string groupID)
{
	if (m_pStarRtcCore != NULL)
	{
		m_pStarRtcCore->applyDelGroup((char*)groupID.c_str());
	}
	return true;
}

/**
 * 添加群成员
 * @param groupID
 * @param memberIDs
 */
void CGroupManager::addGroupMembers(string groupID, list<string> memberIDs)
{
	if (memberIDs.size() <= 0)
	{
		return;
	}
	string strIds = "";
	list<string>::iterator iter = memberIDs.begin();
	for (; iter != memberIDs.end(); iter++)
	{
		if (strIds != "")
		{
			strIds = "," + strIds;
		}
		strIds = strIds + *iter;
	}
	if (m_pStarRtcCore != NULL)
	{
		m_pStarRtcCore->applyAddUserToGroup((char*)groupID.c_str(), (char*)strIds.c_str(), "");
	}
}

/**
 * 删除群成员
 * @param groupID
 * @param memberIDs
 */
void CGroupManager::deleteGroupMembers(string groupID, list<string> memberIDs)
{
	if (memberIDs.size() <= 0)
	{
		return;
	}
	string strIds = "";
	list<string>::iterator iter = memberIDs.begin();
	for (; iter != memberIDs.end(); iter++)
	{
		if (strIds != "")
		{
			strIds = "," + strIds;
		}
		strIds = strIds + *iter;
	}
	if (m_pStarRtcCore != NULL)
	{
		m_pStarRtcCore->applyRemoveUserToGroup((char*)groupID.c_str(), (char*)strIds.c_str());
	}
}

/**
 * 设置推送开关
 * @param groupID
 * @param enable
 * @param callback
 */
void CGroupManager::setPushEnable(string groupID, bool enable)
{

}

/**
 *发送消息
 * @param groupID
 * @param atUserIDs
 * @param Message
 * @param callback
 * @return 发出的消息
 */
CIMMessage* CGroupManager::sendMessage(string groupID, list<string> atUserIDs, string strMessage)
{
	string strAtList = "";
	list<string>::iterator iter = atUserIDs.begin();
	for (; iter != atUserIDs.end(); iter++)
	{
		if (strAtList != "")
		{
			strAtList = "," + strAtList;
		}
		strAtList = strAtList + *iter;
	}

	CIMMessage* pIMMessage = StarIMMessageBuilder::getGroupMessage(m_pUserManager->m_ServiceParam.m_strUserId, groupID, strAtList, strMessage);
	if (pIMMessage != NULL)
	{
		m_pStarRtcCore->sendGroupMsg(pIMMessage);
	}
	return pIMMessage;
}

/**
 *发送消息
 * @param groupID
 * @param atUserIDs
 * @param Message
 * @param callback
 * @return 发出的消息
 */
CIMMessage* CGroupManager::sendOnlineMessage(string groupID, list<string> atUserIDs, string strMessage)
{
	string strAtList = "";
	list<string>::iterator iter = atUserIDs.begin();
	for (; iter != atUserIDs.end(); iter++)
	{
		if (strAtList != "")
		{
			strAtList = "," + strAtList;
		}
		strAtList = strAtList + *iter;
	}

	CIMMessage* pIMMessage = StarIMMessageBuilder::getGroupMessage(m_pUserManager->m_ServiceParam.m_strUserId, groupID, strAtList, strMessage);
	if (pIMMessage != NULL)
	{
		m_pStarRtcCore->sendOnlineMessage(pIMMessage);
	}
	return pIMMessage;
}

/**
 * 获取group list回调函数
 */
int CGroupManager::applyGetGroupListFin(list<CGroupInfo>& groupInfoList)
{
	int ret = 0;
	if (CGroupManager::m_pGroupGetListListener)
	{
		ret = CGroupManager::m_pGroupGetListListener->applyGetGroupListFin(groupInfoList);
	}
	return ret;
}

/**
 * 获取用户列表回调函数
 */
int CGroupManager::applyGetUserListFin(list<string>& userList)
{
	int ret = 0;
	if (CGroupManager::m_pGroupGetListListener)
	{
		ret = CGroupManager::m_pGroupGetListListener->applyGetUserListFin(userList);
	}
	return ret;
}

/**
 * 群成员数发生变化
 * @param groupID
 * @param number
 */
void CGroupManager::onMembersUpdeted(string groupID, int number)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onMembersUpdeted(groupID, number);
	}
}

/**
 * 自己被移出群组
 * @param groupID
 */
void CGroupManager::onSelfKicked(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onSelfKicked(groupID);
	}
}

/**
 * 群组已经被删除
 * @param groupID
 */
void CGroupManager::onGroupDeleted(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onGroupDeleted(groupID);
	}
}

/**
 *  收到消息
 * @param message
 */
void CGroupManager::onReceivedMessage(string groupId, CIMMessage* pMessage)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onReceivedMessage(groupId, pMessage);
	}
}

void CGroupManager::onApplyCreateGroupFin(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onApplyCreateGroupFin(groupID);
	}
}

void CGroupManager::onApplyDelGroupFin(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onApplyCreateGroupFin(groupID);
	}
}

void CGroupManager::onApplyAddUserToGroupFin(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onApplyCreateGroupFin(groupID);
	}
}

void CGroupManager::onApplyRemoveUserFromGroupFin(string groupID)
{
	if (m_pGroupManagerListener != NULL)
	{
		m_pGroupManagerListener->onApplyRemoveUserFromGroupFin(groupID);
	}
}
