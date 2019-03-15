#include "stdafx.h"
#include "CChatroomManager.h"
#include "StarRtcCore.h"
#include "HttpClient.h"
#include "json.h"
#include "StarIMMessageBuilder.h"
CChatroomManager::CChatroomManager(CUserManager* pUserManager, IChatroomManagerListener* pChatroomManagerListener)
{
	m_pUserManager = pUserManager;
	m_pChatroomManagerListener = pChatroomManagerListener;
	StarRtcCore::getStarRtcCoreInstance(pUserManager)->addStarIMChatroomListener(this);
	m_ChatRoomId = "";
	m_bJoinChatRoom = false;
	m_strChatRoomServerIp = "";
	m_nChatRoomServerPort = 0;
	resetReturnVal();
}


CChatroomManager::~CChatroomManager()
{
	stopChatRoomConnect();
	StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->addStarIMChatroomListener(this);
}

void CChatroomManager::resetReturnVal()
{
	m_bReturn = false;
	m_bSuccess = false;
	m_strErrInfo = "";
}
void CChatroomManager::setChatroomId(string chatRoomId)
{
	m_ChatRoomId = chatRoomId;
}

/*
* 通过调度获取ChatRoom服务地址
*/
bool CChatroomManager::getChatRoomServerAddr()
{
	bool bRet = false;
	string userId = m_pUserManager->m_ServiceParam.m_strUserId;
	string agentId = m_pUserManager->m_ServiceParam.m_strAgentId;
	m_strChatRoomServerIp = "";
	m_nChatRoomServerPort = 0;

	CString url = "";
	url.Format("http://%s:9907", m_pUserManager->m_ServiceParam.m_strChatServiceIP.c_str());
	string strData = "userId=" + agentId + "_" + userId;
	CString strContent;

	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url, strData.c_str(), strContent);

	string str_json = strContent.GetBuffer(0);
	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素   
	{
		if (root.isMember("status"))
		{
			CString strStatus = root["status"].asCString();
			if (strStatus == "1" &&  root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				string str = data.asCString();
				int pos = str.find(":");
				m_strChatRoomServerIp = str.substr(0, pos);
				str = str.substr(pos + 1, str.length());
				m_nChatRoomServerPort = atoi(str.c_str());
				printf("m_strChatRoomServerIp:%s m_nChatRoomServerPort:%d \n", m_strChatRoomServerIp.c_str(), m_nChatRoomServerPort);
				bRet = true;
			}
		}
	}
	return bRet;
}

/*
* 创建ChatRoom
*/
bool CChatroomManager::createChatRoom(string strName, int chatroomType)
{
	resetReturnVal();
	bool bRet =  StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->createChatRoom(m_strChatRoomServerIp, m_nChatRoomServerPort, strName, chatroomType);
	if (!bRet)
	{
		return bRet;
	}
	while (m_bReturn == false)
	{
		Sleep(10);
	}
	return m_bSuccess;
}

/*
* 加入ChatRoom
*/
bool CChatroomManager::joinChatRoom()
{
	resetReturnVal();
	bool bRet = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->joinChatRoom(m_strChatRoomServerIp, m_nChatRoomServerPort, m_ChatRoomId);
	if (!bRet)
	{
		return bRet;
	}
	while (m_bReturn == false)
	{
		Sleep(10);
	}
	m_bJoinChatRoom = m_bSuccess;
	return m_bSuccess;
}

/*
 * 查询chatroom在线人数
 */
bool CChatroomManager::getOnlineNumber(string strChatroomId)
{
	StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->getOnlineNumber(m_ChatRoomId);
	return true;
}

bool CChatroomManager::banToSendMsg(char* banUserId, int banTime)
{
	resetReturnVal();
	return StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->banToSendMsg(banUserId, banTime);
}

bool CChatroomManager::kickOutUser(char* kickOutUserId)
{
	resetReturnVal();
	return StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->kickOutUser(kickOutUserId);
}

bool CChatroomManager::sendChat(CIMMessage* pIMMessage)
{
	resetReturnVal();
	return StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->sendChat(pIMMessage);
}

bool CChatroomManager::sendPrivateChat(string toUserId, char* msgData)
{
	bool bRet = false;
	resetReturnVal();
	CIMMessage* pMsg = StarIMMessageBuilder::getGhatRoomMessage(m_pUserManager->m_ServiceParam.m_strUserId, m_ChatRoomId, msgData);
	if (pMsg != NULL)
	{
		bRet = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->sendPrivateChat((char*)toUserId.c_str(), pMsg);
	}
	return bRet;
}

bool CChatroomManager::sendChatroomPrivateControlMessage(string targetId, int code)
{
	bool bRet = false;
	resetReturnVal();
	CIMMessage* pMsg = StarIMMessageBuilder::getGhatRoomContrlMessage(m_pUserManager->m_ServiceParam.m_strUserId, m_ChatRoomId, code);
	if (pMsg != NULL)
	{
		bRet = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->sendPrivateChat((char*)targetId.c_str(), pMsg);
	}
	return bRet;

}

bool CChatroomManager::deleteChatRoom()
{
	resetReturnVal();
	return StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->deleteChatRoom();
}

bool CChatroomManager::reportChatroom(string strName, string strRoomId)
{
	bool bRet = false;
	string url = m_pUserManager->m_ServiceParam.m_strRequestListAddr + "/chat/store?ID=" + strRoomId + "&Name=" + strName + "&Creator=" + m_pUserManager->m_ServiceParam.m_strUserId + "&appid=" + m_pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";

	CString strContent;

	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
	return true;
}

/*
*  与ChatRoom断开连接
*/
bool CChatroomManager::stopChatRoomConnect()
{
	bool bReturn = false;
	if (m_bJoinChatRoom)
	{
		resetReturnVal();
		bool bRet = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->stopChatRoomConnect();
		if (!bRet)
		{
			return bRet;
		}
		while (m_bReturn == false)
		{
			Sleep(10);
		}
		m_bJoinChatRoom = m_bSuccess;
		bReturn = m_bSuccess;
	}
	return bReturn;
}

bool CChatroomManager::exit()
{
	bool bRet = false;
	if (m_bJoinChatRoom)
	{
		bRet = stopChatRoomConnect();
	}
	else
	{
		bRet = true;
	}
	return bRet;
}

//聊天室创建成功
void CChatroomManager::chatroomCreateOK(string roomId, int maxContentLen)
{
	m_ChatRoomId = roomId;
	success();
}
//聊天室加入成功
void CChatroomManager::chatroomJoinOK(string roomId, int maxContentLen)
{
	success();
}
//聊天室创建失败
void CChatroomManager::chatroomCreateFailed(string errString)
{
	failed(errString);
}
//聊天室加入失败
void CChatroomManager::chatroomJoinFailed(string roomId, string errString)
{
	failed(errString);
}
//聊天室报错
void CChatroomManager::chatRoomErr(string errString)
{
	failed(errString);
}
//聊天室关闭成功
void CChatroomManager::chatroomStopOK()
{
	success();
}
//聊天室删除成功
void CChatroomManager::chatroomDeleteOK(string roomId)
{
	success();
}
//聊天室删除失败
void CChatroomManager::chatroomDeleteFailed(string roomId, string errString)
{
	failed(errString);
}
//聊天室禁言成功
void CChatroomManager::chatroomBanToSendMsgOK(string banUserId, int banTime)
{
}
//聊天室禁言失败
void CChatroomManager::chatroomBanToSendMsgFailed(string banUserId, int banTime, string errString)
{
	success();
}
//聊天室踢人成功
void CChatroomManager::chatroomKickOutOK(string kickOutUserId)
{
	success();
}
//聊天余额不足
void CChatroomManager::chatroomSendMsgNoFee()
{
}
//聊天室踢人失败
void CChatroomManager::chatroomKickOutFailed(string kickOutUserId, string errString)
{
	failed(errString);
}
//聊天室 自己被禁言
void CChatroomManager::chatroomSendMsgBanned(int remainTimeSec)
{
}
//聊天室 自己被踢出
void CChatroomManager::chatroomKickedOut()
{
	if (m_pChatroomManagerListener != NULL)
	{
		m_pChatroomManagerListener->onSelfKicked();
	}
}
//聊天室 收到消息
void CChatroomManager::chatroomGetNewMsg(CIMMessage* pMsg)
{
	if (m_pChatroomManagerListener != NULL)
	{
		m_pChatroomManagerListener->onReceivedMessage(pMsg);
	}
}
//聊天室 收到私信消息
void CChatroomManager::chatroomGetNewPrivateMsg(CIMMessage* pMsg)
{
	if (m_pChatroomManagerListener != NULL)
	{
		m_pChatroomManagerListener->onReceivePrivateMessage(pMsg);
	}
}
//聊天室在线人数
void CChatroomManager::getRoomOnlineNumber(string roomId, int number)
{
	if (m_pChatroomManagerListener != NULL)
	{
		m_pChatroomManagerListener->onMembersUpdated(number);
	}
}
//聊天室在线人数
void CChatroomManager::sendMessageSuccess(int msgIndx)
{

}
//聊天室在线人数
void CChatroomManager::sendMessageFailed(int msgIndx)
{
}
//收到控制消息
void CChatroomManager::revControlMessage(string fromID, int code)
{
}

/**
 * 成功
 * @param data
 */
void CChatroomManager::success()
{
	m_bSuccess = true;
	m_bReturn = true;
}

/**
 * 失败
 * @param errMsg
 */
void CChatroomManager::failed(string errMsg)
{
	m_bSuccess = false;
	m_strErrInfo = errMsg;
	m_bReturn = true;
}

string CChatroomManager::getChatroomId()
{
	return m_ChatRoomId;
}
