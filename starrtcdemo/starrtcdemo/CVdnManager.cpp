#include "stdafx.h"
#include "CVdnManager.h"
#include "HttpClient.h"
#include "json.h"
#include "StarRtcCore.h"
CVdnManager::CVdnManager(CUserManager* pUserManager, IVdnManagerListener* pVdnManagerListener):ILiveInterface(pUserManager)
{
	m_liveType = LIVE_TYPE_VDN;
	m_pVdnManagerListener = pVdnManagerListener;
	m_strApplyDownloadChannelServerIp = "";
	m_nApplyDownloadChannelServerPort = 0;
	m_bApplayDownload = false;
	StarRtcCore* pStarRtcCore = StarRtcCore::getStarRtcCoreInstance(pUserManager);
	pStarRtcCore->addVdnListener(this);
	StarRtcCore::getStarRtcCoreInstance(pUserManager)->addRecvDataListener(this);
}


CVdnManager::~CVdnManager()
{
	m_strApplyDownloadChannelServerIp = "";
	m_nApplyDownloadChannelServerPort = 0;
	if (m_bApplayDownload)
	{
		stopLiveDownload();
	}
	StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->addVdnListener(NULL);
	StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->addRecvDataListener(NULL);
}

/*
* 通过调度获取Channel服务地址
*/
bool CVdnManager::getApplyDownloadChannelServerAddr()
{
	string userId = m_pUserManager->m_ServiceParam.m_strUserId;
	string agentId = m_pUserManager->m_ServiceParam.m_strAgentId;
	bool bRet = false;
	m_strApplyDownloadChannelServerIp = "";
	m_nApplyDownloadChannelServerPort = 0;
	if (m_pUserManager->m_bUserDispatch == false)
	{
		m_strApplyDownloadChannelServerIp = m_pUserManager->m_ServiceParam.m_strDownloadServiceIP;
		m_nApplyDownloadChannelServerPort = m_pUserManager->m_ServiceParam.m_nDownloadServicePort;
		bRet = true;
		return bRet;
	}
	CString url = "";
	url.Format("http://%s:%d", m_pUserManager->m_ServiceParam.m_strDownloadServiceIP.c_str(), m_pUserManager->m_ServiceParam.m_nDownloadServicePort);

	string strData = "channelId=" + m_ChannelId + "&userId=" + agentId + "_" + userId;
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
				if (data.isMember("ip") && data.isMember("port"))
				{
					m_strApplyDownloadChannelServerIp = data["ip"].asCString();
					string str = data["port"].asCString();;
					m_nApplyDownloadChannelServerPort = atoi(str.c_str());
					printf("m_strApplyDownloadChannelServerIp:%s m_nChannelServerPort:%d \n", m_strApplyDownloadChannelServerIp.c_str(), m_nApplyDownloadChannelServerPort);
					bRet = true;
				}
			}
		}
	}
	return bRet;
}

/*
* Channel 申请下载
*/
bool CVdnManager::applyDownload()
{
	bool bret = false;
	m_bApplayDownload = false;
	resetReturnVal();
	bret = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->applyDownload((char*)m_strApplyDownloadChannelServerIp.c_str(), m_nApplyDownloadChannelServerPort, (char*)m_ChannelId.c_str());
	if(bret == false)
	{
		bret = false;
	}
	while (m_bReturn == false)
	{
		Sleep(10);
	}
	bret = m_bSuccess;
	m_bApplayDownload = m_bSuccess;
	return bret;
}

/*
* Channel 停止下载
*/
bool CVdnManager::stopLiveDownload()
{
	bool bret = false;
	if (m_bApplayDownload == false)
	{
		return true;
	}
	resetReturnVal();
	bret = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->stopDownload();

	if (bret == false)
	{
		bret = false;
	}
	while (m_bReturn == false)
	{
		Sleep(10);
	}
	bret = m_bSuccess;
	if (m_bSuccess)
	{
		m_bApplayDownload = false;
	}
	return bret;
}

/*
* 设置数据流配置
*/
bool CVdnManager::setStreamConfig(int* sendBuf, int length)
{
	bool bret = false;
	resetReturnVal();
	bret = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->setStreamConfigVdn(sendBuf, length);
	while (m_bReturn == false)
	{
		Sleep(10);
	}
	bret = m_bSuccess;
	return true;
}


int CVdnManager::applyDownloadChannelOK()
{
	success();
	return 0;
}
int CVdnManager::applyDownloadChannelFailed(char* errString)
{
	failed(errString);
	return 0;
}
int CVdnManager::downloadChannelError(char* errString)
{
	failed(errString);
	return 0;
}
int CVdnManager::downloadStopOK()
{
	success();
	return 0;
}
int CVdnManager::downloadChannelClosed()
{
	m_bApplayDownload = false;
	if (m_pVdnManagerListener != NULL)
	{
		m_pVdnManagerListener->downloadChannelClosed();
	}	
	return 0;
}
int CVdnManager::downloadChannelLeave()
{
	m_bApplayDownload = false;
	if (m_pVdnManagerListener != NULL)
	{
		m_pVdnManagerListener->downloadChannelLeave();
	}
	return 0;
}
int CVdnManager::downloadNetworkUnnormal()
{
	if (m_pVdnManagerListener != NULL)
	{
		m_pVdnManagerListener->downloadNetworkUnnormal();
	}
	return 0;
}
int CVdnManager::queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum)
{
	if (m_pVdnManagerListener != NULL)
	{
		m_pVdnManagerListener->queryVDNChannelOnlineNumberFin(channelId, totalOnlineNum);
	}
	return 0;
}
int CVdnManager::uploaderAdd(char* upUserId, int upId)
{
	if (m_pVdnManagerListener != NULL)
	{
		m_pVdnManagerListener->uploaderAddVdn(upUserId, upId);
	}

	return 0;
}
int CVdnManager::uploaderRemove(char* upUserId, int upId)
{
	if (m_pVdnManagerListener != NULL)
	{
		m_pVdnManagerListener->uploaderRemoveVdn(upUserId, upId);
	}	
	return 0;
}
int CVdnManager::downloadStreamConfigOK(char* channelId)
{
	success();
	return 0;
}
int CVdnManager::downloadStreamConfigFailed()
{
	failed("");
	return 0;
}
int CVdnManager::getRealtimeData(int upId, uint8_t* data, int len)
{
	if (m_pVdnManagerListener != NULL)
	{
		m_pVdnManagerListener->getRealtimeDataVdn(upId, data, len);
	}
	return 0; 
}
int CVdnManager::getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_pVdnManagerListener != NULL)
	{
		m_pVdnManagerListener->getVideoRawVdn(upId, w, h, videoData, videoDataLen);
	}
	return 0;
}

