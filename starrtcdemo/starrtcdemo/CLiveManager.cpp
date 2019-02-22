#include "stdafx.h"
#include "CLiveManager.h"
#include "CVdnManager.h"
#include "CSrcManager.h"
#include "HttpClient.h"
CLiveManager::CLiveManager(CUserManager* pUserManager, IChatroomManagerListener* pChatroomManagerListener, IVdnManagerListener* pVdnManagerListener, ISrcManagerListener* pSrcManagerListener)
{
	m_pVdnManagerListener = pVdnManagerListener;
	m_pSrcManagerListener = pSrcManagerListener;
	m_pUserManager = pUserManager;
	m_pChatroomManager = new CChatroomManager(m_pUserManager, pChatroomManagerListener);
	m_pLiveInterface = NULL;
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

bool CLiveManager::createLiveAndJoin(string strName, int chatroomType, int channelType)
{
	closeLive();
	bool bRet = m_pChatroomManager->getChatRoomServerAddr();
	if (bRet)
	{
		bRet =  m_pChatroomManager->createChatRoom(strName, chatroomType);
		if (bRet)
		{
			m_pLiveInterface = new CSrcManager(m_pUserManager, m_pSrcManagerListener);
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
					//join channel
					pSrcManager->startEncoder();
					pSrcManager->globalSetting(m_pUserManager->m_ServiceParam.m_BigPic.m_nWidth, m_pUserManager->m_ServiceParam.m_BigPic.m_nHeight, 1024, 15);
					bRet = pSrcManager->applyUpload();
				}
			}		
		}
	}
	
	return bRet;
}
/*
 * 上报chatroom 和 channelID
 */
bool CLiveManager::reportChatRoomAndChannel(string strName, string strChatroomId, string strChannelId)
{
	bool bRet = false;
	string url = "https://api.starrtc.com/public/live/store?ID=" + strChannelId + strChatroomId + "&Name=" + strName + "&Creator=" + m_pUserManager->m_ServiceParam.m_strUserId + "&appid=" + m_pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";

	CString strContent;

	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
	bRet = true;
	return true;
}

bool CLiveManager::joinLive(string strChatroomId, string strChannelId, bool bSelfCreate)
{
	closeLive();

	m_pChatroomManager->setChatroomId(strChatroomId);
	bool bRet = m_pChatroomManager->getChatRoomServerAddr();
	
	if (bRet)
	{
		bRet = m_pChatroomManager->joinChatRoom();
		if (bRet)
		{
			if (bSelfCreate)
			{
				m_pLiveInterface = new CSrcManager(m_pUserManager, m_pSrcManagerListener);
				m_pLiveInterface->setChannelId(strChannelId);
				CSrcManager* pSrcManager = (CSrcManager*)m_pLiveInterface;
				pSrcManager->getChannelServerAddr();
				pSrcManager->startEncoder();
				pSrcManager->globalSetting(m_pUserManager->m_ServiceParam.m_BigPic.m_nWidth, m_pUserManager->m_ServiceParam.m_BigPic.m_nHeight, 1024, 15);
				bRet = pSrcManager->applyUpload();
			}
			else
			{
				m_pLiveInterface = new CVdnManager(m_pUserManager, m_pVdnManagerListener);
				m_pLiveInterface->setChannelId(strChannelId);
				CVdnManager* pVdnManager = (CVdnManager*)m_pLiveInterface;
				pVdnManager->getApplyDownloadChannelServerAddr();
				bRet = pVdnManager->applyDownload();
			}
		}
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
		CVdnManager* pVdnManager = (CVdnManager*)m_pLiveInterface;
		bRet = pVdnManager->setStreamConfig(sendBuf, length);
	}
	return bRet;
}

bool CLiveManager::closeLive()
{
	m_pChatroomManager->stopChatRoomConnect();
	if (m_pLiveInterface != NULL)
	{
		delete m_pLiveInterface;
		m_pLiveInterface = NULL;
	}
	return true;
}
