#include "stdafx.h"
#include "CMeetingManager.h"
#include "StarIMMessageType.h"
#include "HttpClient.h"
CMeetingManager::CMeetingManager(CUserManager* pUserManager, IMeetingManagerListener* pListener)
{
	m_pMeetingManagerListener = pListener;
	m_pUserManager = pUserManager;
	m_pChatroomManager = new CChatroomManager(m_pUserManager, this);
	m_pSrcManager = NULL;
}


CMeetingManager::~CMeetingManager()
{
	m_pMeetingManagerListener = NULL;
	m_pUserManager = NULL;
	if (m_pSrcManager != NULL)
	{
		delete m_pSrcManager;
		m_pSrcManager = NULL;
	}
	if (m_pChatroomManager != NULL)
	{
		delete m_pChatroomManager;
		m_pChatroomManager = NULL;
	}
}

bool CMeetingManager::createAndJoin(string strName, int chatroomType, int channelType, int* streamConfig, int length)
{
	close();
	bool bRet = m_pChatroomManager->getChatRoomServerAddr();
	if (bRet)
	{
		bRet = m_pChatroomManager->createChatRoom(strName, chatroomType);
		if (bRet)
		{
			m_pSrcManager = new CSrcManager(m_pUserManager, this);
			m_pSrcManager->getChannelServerAddr();
			// create channel
			bRet = m_pSrcManager->createChannel(strName, channelType, m_pChatroomManager->getChatroomId());
			if (bRet)
			{
				reportChatRoomAndChannel(strName, m_pChatroomManager->getChatroomId(), m_pSrcManager->getChannelId());
				bRet = m_pChatroomManager->joinChatRoom();
				if (bRet)
				{
					//join channel
					m_pSrcManager->globalSetting(15, 1024);
					bRet = m_pSrcManager->applyUpload();
					m_pSrcManager->startEncoder();
					if (length > 7)
					{
						length = 7;
					}
					setStreamConfig(streamConfig, length);
				}
			}
		}
	}

	return bRet;
}

void CMeetingManager::insertVideoNalu(uint8_t* videoData, int dataLen)
{
	if (m_pSrcManager != NULL)
	{
		m_pSrcManager->insertVideoNalu(videoData, dataLen);
	}
}
void CMeetingManager::insertVideoRaw(uint8_t* videoData, int dataLen, int isBig)
{
	if (m_pSrcManager != NULL)
	{
		m_pSrcManager->insertVideoRaw(videoData, dataLen, isBig);
	}
}

int CMeetingManager::cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall)
{
	int nRet = 0;
	if (m_pSrcManager != NULL)
	{
		nRet = m_pSrcManager->cropVideoRawNV12(w, h, videoData, dataLen, yuvProcessPlan, rotation, needMirror, outVideoDataBig, outVideoDataSmall);
	}
	return nRet;
}
/*
 * 上报chatroom 和 channelID
 */
bool CMeetingManager::reportChatRoomAndChannel(string strName, string strChatroomId, string strChannelId)
{
	bool bRet = false;
	string url = m_pUserManager->m_ServiceParam.m_strRequestListAddr + "/meeting/store?ID=" + strChannelId + strChatroomId + "&Name=" + strName + "&Creator=" + m_pUserManager->m_ServiceParam.m_strUserId + "&appid=" + m_pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";

	CString strContent;

	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
	bRet = true;
	return true;
}

bool CMeetingManager::joinChatroom(string strChatroomId)
{
	bool bRet = true;
	if (m_pChatroomManager->getChatroomId() != strChatroomId)
	{
		closeChatroom();
		m_pChatroomManager->setChatroomId(strChatroomId);
		bRet = m_pChatroomManager->getChatRoomServerAddr();

		if (bRet)
		{
			bRet = m_pChatroomManager->joinChatRoom();
		}
		else
		{
			m_pChatroomManager->setChatroomId("");
		}
	}
	return bRet;
}

bool CMeetingManager::join(string strChatroomId, string strChannelId, int* streamConfig, int length)
{
	bool bRet = true;
	closeLive();
	bRet = joinChatroom(strChatroomId);
	if (bRet)
	{
		m_pSrcManager = new CSrcManager(m_pUserManager, this);
		m_pSrcManager->setChannelId(strChannelId);
		m_pSrcManager->getChannelServerAddr();
		m_pSrcManager->globalSetting(15, 1024);
		bRet = m_pSrcManager->applyUpload();
		m_pSrcManager->startEncoder();

		if (length > 7)
		{
			length = 7;
		}
		//setStreamConfig(streamConfig, length);
	}
	return bRet;
}

/*
* 设置数据流配置
*/
bool CMeetingManager::setStreamConfig(int* sendBuf, int length)
{
	bool bRet = false;
	if (m_pSrcManager != NULL)
	{
		bRet = m_pSrcManager->setStreamConfig(sendBuf, length);
	}
	return bRet;
}

bool CMeetingManager::closeChatroom()
{
	m_pChatroomManager->stopChatRoomConnect();
	return true;
}

bool CMeetingManager::closeLive()
{
	if (m_pSrcManager != NULL)
	{
		delete m_pSrcManager;
		m_pSrcManager = NULL;
	}
	return true;
}

bool CMeetingManager::close()
{
	closeLive();
	closeChatroom();
	return true;
}

bool CMeetingManager::applyToBroadcaster(string chatroomId, string channelId, string toId)
{
	bool bRet = false;
	bRet = joinChatroom(chatroomId);
	if (bRet && m_pChatroomManager != NULL)
	{
		bRet = m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_APPLY_LINK);
		if (bRet)
		{
			if (m_pSrcManager != NULL)
			{
				delete m_pSrcManager;
				m_pSrcManager = NULL;
			}
			m_pSrcManager = new CSrcManager(m_pUserManager, this);
			m_pSrcManager->setChannelId(channelId);
		}
	}
	return bRet;
}

void CMeetingManager::agreeApplyToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_APPLY_LINK_AGREE);
	}
	if (m_pSrcManager != NULL)
	{
		m_pSrcManager->setUploader(toId);
	}
}

void CMeetingManager::refuseApplyToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_APPLY_LINK_DISAGREE);
	}
}

void CMeetingManager::inviteToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_INVITE_LINK);
	}
}

void CMeetingManager::agreeInviteToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_INVITE_LINK_AGREE);
	}
}

void CMeetingManager::refuseInviteToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_INVITE_LINK_DISAGREE);
	}
}

/**
 * 聊天室成员数变化
 * @param number
 */
void CMeetingManager::onMembersUpdated(int number)
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->onMembersUpdated(number);
	}
}

/**
 * 自己被踢出聊天室
 */
void CMeetingManager::onSelfKicked()
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->onSelfKicked();
	}
}

/**
 * 自己被踢出聊天室
 */
void CMeetingManager::onSelfMuted(int seconds)
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->onSelfMuted(seconds);
	}
}

/**
 * 聊天室已关闭
 */
void CMeetingManager::onClosed()
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->onClosed();
	}
}

/**
 * 收到消息
 * @param message
 */
void CMeetingManager::onReceivedMessage(CIMMessage* pMessage)
{
	
}

/**
 * 收到私信消息
 * @param message
 */
void CMeetingManager::onReceivePrivateMessage(CIMMessage* pMessage)
{
	
}

int CMeetingManager::uploaderAddSrc(char* upUserId, int upId)
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->uploaderAdd(upUserId, upId);
	}
	return 0;
}
int CMeetingManager::uploaderRemoveSrc(char* upUserId, int upId)
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->uploaderRemove(upUserId, upId);
	}
	return 0;
}
int CMeetingManager::getRealtimeDataSrc(int upId, uint8_t* data, int len)
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->getRealtimeData(upId, data, len);
	}
	return 0;
}
int CMeetingManager::getVideoRawSrc(int upId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->getVideoRaw(upId, w, h, videoData, videoDataLen);
	}
	return 0;
}

int CMeetingManager::deleteChannel(char* channelId)
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->deleteChannel(channelId);
	}
	return 0;
}
int CMeetingManager::stopOK()
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->stopOK();
	}
	return 0;
}
int CMeetingManager::srcError(char* errString)
{
	if (m_pMeetingManagerListener != NULL)
	{
		m_pMeetingManagerListener->srcError(errString);
	}
	return 0;
}
