#include "stdafx.h"
#include "CSrcManager.h"
#include "HttpClient.h"
#include "json.h"
#include "StarRtcCore.h"

CSrcManager::CSrcManager(CUserManager* pUserManager, ISrcManagerListener* pSrcManagerListener) :ILiveInterface(pUserManager)
{
	m_strApplyUploadChannelServerIp = "";
	m_nApplyUploadChannelServerPort = 0;
	m_bApplyUpload = false;
	m_pSrcManagerListener = pSrcManagerListener;
	StarRtcCore::getStarRtcCoreInstance(pUserManager)->addSrcListener(this);
}


CSrcManager::~CSrcManager()
{
	stop();
}

/*
* 全局参数设置
*/
void CSrcManager::globalSetting(int w, int h, int fps, int bitrate)
{
	printf("globalSetting w:%d, h:%d, fps:%d, bitrate:%d\n", w, h, fps, bitrate);
	StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->setGlobalSetting(1, 0,
		0,
		w, h, fps, bitrate,
		0, 0, 0, 0,
		0, 0, 0);
}

/*
* 通过调度获取Channel服务地址
*/
bool CSrcManager::getChannelServerAddr()
{
	string userId = m_pUserManager->m_ServiceParam.m_strUserId;
	string agentId = m_pUserManager->m_ServiceParam.m_strAgentId;
	bool bRet = false;
	m_strApplyUploadChannelServerIp = "";
	m_nApplyUploadChannelServerPort = 0;
	CString url = "";
	url.Format("http://%s:9929", m_pUserManager->m_ServiceParam.m_strUploadServiceIP.c_str());


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
				if (data.isMember("ip") && data.isMember("port"))
				{
					m_strApplyUploadChannelServerIp = data["ip"].asCString();
					string str = data["port"].asCString();;
					m_nApplyUploadChannelServerPort = atoi(str.c_str());
					printf("m_strApplyUploadChannelServerIp:%s m_nApplyUploadChannelServerPort:%d \n", m_strApplyUploadChannelServerIp.c_str(), m_nApplyUploadChannelServerPort);
					bRet = true;
				}
			}
		}
	}
	return bRet;
}

/*
* 创建Channel
*/
bool CSrcManager::createChannel(string strName, int channelType, string strChatroomId)
{
	bool bret = false;
	resetReturnVal();
	bret = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->createPublicChannel((char*)m_strApplyUploadChannelServerIp.c_str(), m_nApplyUploadChannelServerPort, strName, channelType, strChatroomId);
	if (bret == false)
	{
		bret = false;
	}
	while (m_bReturn == false)
	{
		Sleep(10);
	}
	bret = m_bSuccess;
	return bret;
}

/*
 * Channel 申请上传
 */
bool CSrcManager::applyUpload()
{
	bool bret = false;
	resetReturnVal();
	bret = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->startUploadSrcServer((char*)m_strApplyUploadChannelServerIp.c_str(), m_nApplyUploadChannelServerPort, (char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), (char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(), (char*)m_pUserManager->m_strTokenId.c_str(), (char*)m_ChannelId.c_str());
	if (bret == false)
	{
		bret = false;
	}
	while (m_bReturn == false)
	{
		Sleep(10);
	}
	bret = m_bSuccess;
	return bret;
}

/*
 * 开启直播编码器
 */
bool CSrcManager::startEncoder()
{
	return StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->startLiveSrcEncoder(0, 0, 0, 0);
}

/*
 * Channel 停止上传
 */
bool CSrcManager::stopUpload()
{
	bool bret = false;
	resetReturnVal();
	bret = StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->stopUploadSrcServer();
	if (bret == false)
	{
		bret = false;
	}
	while (m_bReturn == false)
	{
		Sleep(10);
	}
	bret = m_bSuccess;
	return bret;
	return true;
}

/*
 *  停止直播编码器
 */
bool CSrcManager::stopEncoder()
{
	StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->stopLiveSrcCodec();
	return true;
}

bool CSrcManager::stop()
{
	bool bRet = stopUpload();
	stopEncoder();
	return bRet;
}

int CSrcManager::createChannelOK(char* channelId)
{
	m_ChannelId = channelId;
	success();
	return 0;
}

int CSrcManager::createChannelFailed(char* errString)
{
	failed(errString);
	return 0;
}

int CSrcManager::applyUploadChannelOK(char* channelId)
{
	success();
	return 0;
}

int CSrcManager::applyUploadChannelFailed(char* errString, char* channelId)
{
	failed(errString);
	return 0;
}

int CSrcManager::setUploaderOK(char* channelId, char* uploadUserId)
{
	success();
	return 0;
}

int CSrcManager::setUploaderFailed(char* errString, char* channelId, char* uploadUserId)
{
	failed(errString);
	return 0;
}

int CSrcManager::unsetUploaderOK(char* channelId, char* uploadUserId)
{
	success();
	return 0;
}

int CSrcManager::unsetUploaderFailed(char* errString, char* channelId, char* uploadUserId)
{
	failed(errString);
	return 0;
}

int CSrcManager::muteUploaderOK(char* channelId, char* uploadUserId)
{
	success();
	return 0;
}

int CSrcManager::muteUploaderFailed(char* errString, char* channelId, char* uploadUserId)
{
	failed(errString);
	return 0;
}

int CSrcManager::unmuteUploaderOK(char* channelId, char* uploadUserId)
{
	success();
	return 0;
}

int CSrcManager::unmuteUploaderFailed(char* errString, char* channelId, char* uploadUserId)
{
	failed(errString);
	return 0;
}

int CSrcManager::deleteChannelOK(char* channelId)
{
	success();
	return 0;
}

int CSrcManager::deleteChannelFailed(char* errString, char* channelId)
{
	failed(errString);
	return 0;
}

int CSrcManager::uploadUnseted(char* channelId)
{
	return 0;
}

int CSrcManager::uploadMuted(char* channelId)
{
	return 0;
}
int CSrcManager::uploadUnmuted(char* channelId)
{
	return 0;
}

int CSrcManager::setPeerStreamDownloadConfigOK(char* channelId)
{
	success();
	return 0;
}
int CSrcManager::setPeerStreamDownloadConfigFailed(char* channelId)
{
	failed("");
	return 0;
}

int CSrcManager::stopOK()
{
	success();
	if (m_pSrcManagerListener != NULL)
	{
		m_pSrcManagerListener->stopOK();
	}
	return 0;
}
int CSrcManager::isRetrying()
{
	return 0;
}
int CSrcManager::networkUnnormal()
{
	return 0;
}

int CSrcManager::srcError(char* errString)
{
	failed("");
	if (m_pSrcManagerListener != NULL)
	{
		m_pSrcManagerListener->srcError(errString);
	}
	return 0;
}
int CSrcManager::querySrcChannelOnlineNumberFin(char* channelId, int totalOnlineNum)
{
	return 0;
}

int CSrcManager::uploaderAddSrc(char* upUserId, int upId)
{
	if (m_pSrcManagerListener != NULL)
	{
		m_pSrcManagerListener->uploaderAdd(upUserId, upId);
	}
	return 0;
}
int CSrcManager::uploaderRemoveSrc(char* upUserId, int upId)
{
	if (m_pSrcManagerListener != NULL)
	{
		m_pSrcManagerListener->uploaderRemove(upUserId, upId);
	}
	return 0;
}
int CSrcManager::getRealtimeDataSrc(int upId, uint8_t* data, int len)
{
	if (m_pSrcManagerListener != NULL)
	{
		m_pSrcManagerListener->getRealtimeData(upId, data, len);
	}
	return 0;
}

int CSrcManager::getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen)
{
	if (m_pSrcManagerListener != NULL)
	{
		m_pSrcManagerListener->getVideoRaw(upId, w, h, videoData, videoDataLen);
	}
	return 0;
}
