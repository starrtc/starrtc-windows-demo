#include "stdafx.h"
#include "CLiveManager.h"
#include "CVdnManager.h"
#include "CSrcManager.h"
#include "HttpClient.h"
#include "StarIMMessageType.h"
#include "CropType.h"
CLiveManager::CLiveManager(CUserManager* pUserManager, ILiveListener* pLiveListener)
{
	m_pUserManager = pUserManager;
	m_pLiveListener = pLiveListener;
	m_pChatroomManager = new CChatroomManager(m_pUserManager, this);
	m_pLiveInterface = NULL;
	//memset(m_configArr, 1, sizeof(m_configArr));
	
}


CLiveManager::~CLiveManager()
{
	if (m_pLiveInterface != NULL)
	{
		delete m_pLiveInterface;
		m_pLiveInterface = NULL;
	}
	if (m_pChatroomManager != NULL)
	{
		delete m_pChatroomManager;
		m_pChatroomManager = NULL;
	}
}

bool CLiveManager::createLiveAndJoin(string strName, int chatroomType, int channelType, int* streamConfig, int length)
{
	close();
	bool bRet = m_pChatroomManager->getChatRoomServerAddr();
	if (bRet)
	{
		bRet =  m_pChatroomManager->createChatRoom(strName, chatroomType);
		if (bRet)
		{
			m_pLiveInterface = new CSrcManager(m_pUserManager, this);
			CSrcManager* pSrcManager = (CSrcManager*)m_pLiveInterface;
			pSrcManager->getChannelServerAddr();
			// create channel
			bRet = pSrcManager->createChannel(strName, channelType, m_pChatroomManager->getChatroomId());
			if (bRet)
			{
				reportChatRoomAndChannel(strName, m_pChatroomManager->getChatroomId(), pSrcManager->getChannelId());
				bRet = m_pChatroomManager->joinChatRoom();
				if (bRet)
				{
					//join channe
					pSrcManager->globalSetting(15, 1024);
					bRet = pSrcManager->applyUpload();
					pSrcManager->startEncoder(m_pUserManager->m_AudioParam.m_nSampleRateInHz, m_pUserManager->m_AudioParam.m_nChannels, m_pUserManager->m_AudioParam.m_nBitRate, 0);
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

void CLiveManager::insertAudioRaw(uint8_t* audioData, int dataLen)
{
	if (m_pLiveInterface != NULL)
	{
		((CSrcManager*)m_pLiveInterface)->insertAudioRaw(audioData, dataLen);
	}
}


void CLiveManager::insertVideoNalu(uint8_t* videoData, int dataLen)
{
	if (m_pLiveInterface != NULL)
	{
		((CSrcManager*)m_pLiveInterface)->insertVideoNalu(videoData, dataLen);
	}
}
void CLiveManager::insertVideoRaw(uint8_t* videoData, int dataLen, int isBig)
{
	if (m_pLiveInterface != NULL)
	{
		((CSrcManager*)m_pLiveInterface)->insertVideoRaw(videoData, dataLen, isBig);
	}
}

int CLiveManager::cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall)
{
	int nRet = 0;
	if (m_pLiveInterface != NULL)
	{
		nRet = ((CSrcManager*)m_pLiveInterface)->cropVideoRawNV12(w, h, videoData, dataLen, yuvProcessPlan, rotation, needMirror, outVideoDataBig, outVideoDataSmall);
	}
	return nRet;
}
/*
 * 上报chatroom 和 channelID
 */
bool CLiveManager::reportChatRoomAndChannel(string strName, string strChatroomId, string strChannelId)
{
	bool bRet = false;
	string url = m_pUserManager->m_ServiceParam.m_strRequestListAddr + "/live/store?ID=" + strChannelId + strChatroomId + "&Name=" + strName + "&Creator=" + m_pUserManager->m_ServiceParam.m_strUserId + "&appid=" + m_pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";

	CString strContent;

	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
	bRet = true;
	return true;
}

bool CLiveManager::joinLive(string strChatroomId, string strChannelId, bool bSelfCreate, int* streamConfig, int length)
{
	bool bRet = true;
	closeLive();
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
	
	if (bRet)
	{	
		if (bSelfCreate)
		{
			m_pLiveInterface = new CSrcManager(m_pUserManager, this);
			m_pLiveInterface->setChannelId(strChannelId);
			CSrcManager* pSrcManager = (CSrcManager*)m_pLiveInterface;
			pSrcManager->getChannelServerAddr();
			pSrcManager->globalSetting(15, 1024);
			bRet = pSrcManager->applyUpload();
			pSrcManager->startEncoder(m_pUserManager->m_AudioParam.m_nSampleRateInHz, m_pUserManager->m_AudioParam.m_nChannels, m_pUserManager->m_AudioParam.m_nBitRate, 0);
			
		}
		else
		{
			m_pLiveInterface = new CVdnManager(m_pUserManager, this);
			m_pLiveInterface->setChannelId(strChannelId);
			CVdnManager* pVdnManager = (CVdnManager*)m_pLiveInterface;
			pVdnManager->getApplyDownloadChannelServerAddr();
			bRet = pVdnManager->applyDownload();
		}	
		if (length > 7)
		{
			length = 7;
		}
		setStreamConfig(streamConfig, length);
	}	
	return bRet;
}

/*
* 设置数据流配置
*/
bool CLiveManager::setStreamConfig(int* sendBuf, int length)
{
	bool bRet = false;
	if (m_pLiveInterface != NULL)
	{
		bRet = m_pLiveInterface->setStreamConfig(sendBuf, length);
	}
	return bRet;
}

bool CLiveManager::closeChatroom()
{
	m_pChatroomManager->stopChatRoomConnect();
	return true;
}

bool CLiveManager::closeLive()
{
	if (m_pLiveInterface != NULL)
	{
		delete m_pLiveInterface;
		m_pLiveInterface = NULL;
	}
	return true;
}

bool CLiveManager::close()
{
	closeLive();
	closeChatroom();
	return true;
}

void CLiveManager::applyToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL && m_pLiveInterface != NULL && m_pLiveInterface->m_liveType == LIVE_TYPE_VDN)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_APPLY_LINK);
	}
}

void CLiveManager::agreeApplyToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_APPLY_LINK_AGREE);
	}
	if (m_pLiveInterface != NULL)
	{
		((CSrcManager*)m_pLiveInterface)->setUploader(toId);
	}
}

void CLiveManager::refuseApplyToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_APPLY_LINK_DISAGREE);
	}
}

void CLiveManager::inviteToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_INVITE_LINK);
	}
}

void CLiveManager::agreeInviteToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_INVITE_LINK_AGREE);
	}
}

void CLiveManager::refuseInviteToBroadcaster(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_INVITE_LINK_DISAGREE);
	}
}

void CLiveManager::commandToAudience(string toId)
{
	if (m_pChatroomManager != NULL)
	{
		m_pChatroomManager->sendChatroomPrivateControlMessage(toId, CONTROL_CODE_LIVE_LINK_STOP);
	}
}

void CLiveManager::querySoundData(uint8_t** pData, int* nLength)
{
	if (m_pLiveInterface != NULL)
	{
		m_pLiveInterface->querySoundData(pData, nLength);
	}
}
/**
 * 聊天室成员数变化
 * @param number
 */
void CLiveManager::onMembersUpdated(int number)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->onMembersUpdated(number);
	}
}

/**
 * 自己被踢出聊天室
 */
void CLiveManager::onSelfKicked()
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->onSelfKicked();
	}
}

/**
 * 自己被踢出聊天室
 */
void CLiveManager::onSelfMuted(int seconds)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->onSelfMuted(seconds);
	}
}

/**
 * 聊天室已关闭
 */
void CLiveManager::onClosed()
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->onClosed();
	}
}

/**
 * 收到消息
 * @param message
 */
void CLiveManager::onReceivedMessage(CIMMessage* pMessage)
{
	if (m_pLiveListener != NULL)
	{
		if (pMessage->m_nType == MSG_TYPE_CONTROL)
		{
			if (m_pLiveListener != NULL)
			{
				switch (pMessage->m_nCode)
				{
				case CONTROL_CODE_LIVE_APPLY_LINK:
					m_pLiveListener->onApplyBroadcast(m_pLiveInterface->getChannelId()+ m_pChatroomManager->getChatroomId(),pMessage->m_strFromId);
					break;
				case CONTROL_CODE_LIVE_APPLY_LINK_AGREE:
					m_pLiveListener->onApplyResponsed(m_pLiveInterface->getChannelId() + m_pChatroomManager->getChatroomId(), true);
					break;
				case CONTROL_CODE_LIVE_APPLY_LINK_DISAGREE:
					m_pLiveListener->onApplyResponsed(m_pLiveInterface->getChannelId() + m_pChatroomManager->getChatroomId(), false);
					break;
				default:
					break;
				}
			}
			
			m_pLiveListener->onReceivedMessage(pMessage);
		}
		else if(pMessage->m_nType == MSG_TYPE_CUSTOMER)
		{
			m_pLiveListener->onReceivedMessage(pMessage);
		}	
	}
}

/**
 * 收到私信消息
 * @param message
 */
void CLiveManager::onReceivePrivateMessage(CIMMessage* pMessage)
{
	if (pMessage->m_nType == MSG_TYPE_CONTROL)
	{
		switch (pMessage->m_nCode)
		{
		case CONTROL_CODE_LIVE_APPLY_LINK:
		{
			if (m_pLiveListener != NULL)
			{
				m_pLiveListener->onApplyBroadcast(pMessage->m_strTargetId, pMessage->m_strFromId);
			}
		}
			break;
		case CONTROL_CODE_LIVE_APPLY_LINK_AGREE:
		{
			if (m_pLiveListener != NULL)
			{
				m_pLiveListener->onApplyResponsed(pMessage->m_strTargetId, true);
			}
		}
			break;
		case CONTROL_CODE_LIVE_APPLY_LINK_DISAGREE:
		{
			if (m_pLiveListener != NULL)
			{
				m_pLiveListener->onApplyResponsed(pMessage->m_strTargetId, false);
			}
		}
			break;
		case CONTROL_CODE_LIVE_INVITE_LINK:
		{
		}
			break;
		case CONTROL_CODE_LIVE_INVITE_LINK_AGREE:
		{
		}
			break;

		case CONTROL_CODE_LIVE_INVITE_START_LINK:
		{
		}
			break;

		case CONTROL_CODE_LIVE_INVITE_LINK_DISAGREE:
		{
		}
			break;
		default:
			break;
		}
	}
	else
	{
		if (m_pLiveListener != NULL)
		{
			m_pLiveListener->onReceivedMessage(pMessage);
		}
	}
}

int CLiveManager::uploaderAddVdn(char* upUserId, int upId)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->uploaderAdd(upUserId, upId);
	}
	return 0;
}
int CLiveManager::uploaderRemoveVdn(char* upUserId, int upId)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->uploaderRemove(upUserId, upId);
	}
	return 0;
}
int CLiveManager::getRealtimeDataVdn(int upId, uint8_t* data, int len)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->getRealtimeData(upId, data, len);
	}
	return 0;
}
int CLiveManager::getVideoRawVdn(int upId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->getVideoRaw(upId, w, h, videoData, videoDataLen);
	}
	return 0;
}

int CLiveManager::downloadChannelClosed()
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->downloadChannelClosed();
	}
	return 0;
}
int CLiveManager::downloadChannelLeave()
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->downloadChannelLeave();
	}
	return 0;
}
int CLiveManager::downloadNetworkUnnormal()
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->downloadNetworkUnnormal();
	}
	return 0;
}
int CLiveManager::queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->queryVDNChannelOnlineNumberFin(channelId, totalOnlineNum);
	}
	return 0;
}

int CLiveManager::uploaderAddSrc(char* upUserId, int upId)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->uploaderAdd(upUserId, upId);
	}
	return 0;
}
int CLiveManager::uploaderRemoveSrc(char* upUserId, int upId)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->uploaderRemove(upUserId, upId);
	}
	return 0;
}
int CLiveManager::getRealtimeDataSrc(int upId, uint8_t* data, int len)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->getRealtimeData(upId, data, len);
	}
	return 0;
}
int CLiveManager::getVideoRawSrc(int upId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->getVideoRaw(upId, w, h, videoData, videoDataLen);
	}
	return 0;
}

int CLiveManager::deleteChannel(char* channelId)
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->deleteChannel(channelId);
	}
	return 0;
}
int CLiveManager::stopOK()
{
	if (m_pLiveListener != NULL)
	{
		m_pLiveListener->stopOK();
	}
	return 0;
}
int CLiveManager::srcError(char* errString)
{
	string str = errString;
	if (m_pLiveListener != NULL && str.length() > 0)
	{
		m_pLiveListener->srcError(errString);
	}
	return 0;
}

