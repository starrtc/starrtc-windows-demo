#include "stdafx.h"
#include "CGroupManager.h"
#include "StarIMMessageBuilder.h"

CGroupManager::CGroupManager(CUserManager* pUserManager)
{
	m_pGroupManagerListener = NULL;
	m_pStarRtcCore = StarRtcCore::getStarRtcCoreInstance(pUserManager);
	m_pStarRtcCore->addGroupListener(this);
}


CGroupManager::~CGroupManager()
{
	m_pGroupManagerListener = NULL;
	m_pStarRtcCore->addGroupListener(NULL);
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

	CIMMessage* pIMMessage = StarIMMessageBuilder::getGroupMessage(m_pStarRtcCore->m_pUserManager->m_ServiceParam.m_strUserId, groupID, strAtList, strMessage);
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

	CIMMessage* pIMMessage = StarIMMessageBuilder::getGroupMessage(m_pStarRtcCore->m_pUserManager->m_ServiceParam.m_strUserId, groupID, strAtList, strMessage);
	if (pIMMessage != NULL)
	{
		m_pStarRtcCore->sendOnlineMessage(pIMMessage);
	}
	return pIMMessage;
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
