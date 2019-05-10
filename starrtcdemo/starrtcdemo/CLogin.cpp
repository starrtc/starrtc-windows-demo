#include "stdafx.h"
#include "CLogin.h"
#include "json.h"

#include "HttpClient.h"
#include "StarRtcCore.h"
CLogin::CLogin(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
	StarRtcCore::getStarRtcCoreInstance()->setLogFile("test");
	StarRtcCore::getStarRtcCoreInstance()->setconfigLog(3, 31, 1);
	//StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->saveFile(1);
	m_pUserManager->m_AudioParam.m_nSampleRateInHz = AUDIO_SAMPLE_RATE;
	m_pUserManager->m_AudioParam.m_nChannels = AUDIO_CHANNELS;
	m_pUserManager->m_AudioParam.m_nBitRate = AUDIO_BIT_RATE;
}


CLogin::~CLogin()
{
}

bool CLogin::readConfig()
{
	//向D盘写入程序数据库连接ini文件信息，默认设置如下
	string strPath = ".\\param.ini";
	//CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用
	//BOOL ifFind = finder.FindFile(strPath);
	if (true)
	{

		char buf[256] = { 0 };
		::GetPrivateProfileString("param", "userId", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strUserId = buf;
		if (m_pUserManager->m_ServiceParam.m_strUserId == "")
		{
			srand((int)time(0));
			int nUserId = rand() % 1000000 + 1000000;
			char s[12];             //设定12位对于存储32位int值足够  
			sprintf_s(s, "%d", nUserId);
			m_pUserManager->m_ServiceParam.m_strUserId = s;
			::WritePrivateProfileString("param", "userId", m_pUserManager->m_ServiceParam.m_strUserId.c_str(), strPath.c_str());
		}

		::GetPrivateProfileString("param", "appId", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strAgentId = buf;
		::GetPrivateProfileString("param", "loginServiceIP", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strLoginServiceIP = buf;
		::GetPrivateProfileString("param", "loginServicePort", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_nLoginServicePort = atoi(buf);

		::GetPrivateProfileString("param", "msgServiceIP", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strMessageServiceIP = buf;
		::GetPrivateProfileString("param", "msgServicePort", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_nMessageServicePort = atoi(buf);

		::GetPrivateProfileString("param", "chatServiceIP", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strChatServiceIP = buf;
		::GetPrivateProfileString("param", "chatServicePort", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_nChatServicePort = atoi(buf);

		::GetPrivateProfileString("param", "uploadServiceIP", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strUploadServiceIP = buf;
		::GetPrivateProfileString("param", "uploadServicePort", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_nUploadServicePort = atoi(buf);

		::GetPrivateProfileString("param", "downloadServiceIP", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strDownloadServiceIP = buf;
		::GetPrivateProfileString("param", "downloadServicePort", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_nDownloadServicePort = atoi(buf);

		::GetPrivateProfileString("param", "voipServiceIP", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strVOIPServiceIP = buf;
		::GetPrivateProfileString("param", "voipServicePort", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_nVOIPServicePort = atoi(buf);

		::GetPrivateProfileString("param", "requestListAddr", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strRequestListAddr = buf;

		::GetPrivateProfileString("param", "rate", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_FrameRate = atoi(buf);

		::GetPrivateProfileString("param", "cropType", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_CropType = atoi(buf);

		::GetPrivateProfileString("param", "dispatch", "", buf, sizeof(buf), strPath.c_str());
		int nDispatch = atoi(buf);
		if (nDispatch == 0)
		{
			m_pUserManager->m_bUserDispatch = false;
		}
		else
		{
			m_pUserManager->m_bUserDispatch = true;
		}

		::GetPrivateProfileString("param", "VoipP2P", "", buf, sizeof(buf), strPath.c_str());
		int nP2P = atoi(buf);
		if (nP2P == 0)
		{
			m_pUserManager->m_bVoipP2P = false;
		}
		else
		{
			m_pUserManager->m_bVoipP2P = true;
		}
	}
	return true;
}

bool CLogin::writeConfig()
{
	string strPath = ".\\param.ini";
	//CFileFind finder;
	//BOOL ifFind = finder.FindFile(strPath);
	if (true)
	{
		char buf[128] = { 0 };
		::WritePrivateProfileString("param", "userId", m_pUserManager->m_ServiceParam.m_strUserId.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "appId", m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "loginServiceIP", m_pUserManager->m_ServiceParam.m_strLoginServiceIP.c_str(), strPath.c_str());		
		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nLoginServicePort);
		::WritePrivateProfileString("param", "loginServicePort", buf, strPath.c_str());

		::WritePrivateProfileString("param", "msgServiceIP", m_pUserManager->m_ServiceParam.m_strMessageServiceIP.c_str(), strPath.c_str());
		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nMessageServicePort);
		::WritePrivateProfileString("param", "msgServicePort", buf, strPath.c_str());

		::WritePrivateProfileString("param", "chatServiceIP", m_pUserManager->m_ServiceParam.m_strChatServiceIP.c_str(), strPath.c_str());
		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nChatServicePort);
		::WritePrivateProfileString("param", "chatServicePort", buf, strPath.c_str());

		::WritePrivateProfileString("param", "uploadServiceIP", m_pUserManager->m_ServiceParam.m_strUploadServiceIP.c_str(), strPath.c_str());
		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nUploadServicePort);
		::WritePrivateProfileString("param", "uploadServicePort", buf, strPath.c_str());

		::WritePrivateProfileString("param", "downloadServiceIP", m_pUserManager->m_ServiceParam.m_strDownloadServiceIP.c_str(), strPath.c_str());
		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nDownloadServicePort);
		::WritePrivateProfileString("param", "downloadServicePort", buf, strPath.c_str());

		::WritePrivateProfileString("param", "voipServiceIP", m_pUserManager->m_ServiceParam.m_strVOIPServiceIP.c_str(), strPath.c_str());
		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nVOIPServicePort);
		::WritePrivateProfileString("param", "voipServicePort", buf, strPath.c_str());

		::WritePrivateProfileString("param", "requestListAddr", m_pUserManager->m_ServiceParam.m_strRequestListAddr.c_str(), strPath.c_str());


		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_FrameRate);
		::WritePrivateProfileString("param", "rate", buf, strPath.c_str());

		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_CropType);
		::WritePrivateProfileString("param", "cropType", buf, strPath.c_str());

		memset(buf, 0, sizeof(buf));
		if (m_pUserManager->m_bUserDispatch)
		{
			sprintf_s(buf, "%d",1);
		}
		else
		{
			sprintf_s(buf, "%d", 0);
		}	
		::WritePrivateProfileString("param", "dispatch", buf, strPath.c_str());	

		memset(buf, 0, sizeof(buf));
		if (m_pUserManager->m_bVoipP2P)
		{
			sprintf_s(buf, "%d", 1);
		}
		else
		{
			sprintf_s(buf, "%d", 0);
		}
		::WritePrivateProfileString("param", "VoipP2P", buf, strPath.c_str());
	}
	return true;
}

string CLogin::getServiceParam()
{
	string strRet = "";
	char buf[128] = { 0 };
	strRet = "\"userId\":\"" + m_pUserManager->m_ServiceParam.m_strUserId
		+ "\",\"agentId\":\"" + m_pUserManager->m_ServiceParam.m_strAgentId
		+ "\",\"loginIP\":\"" + m_pUserManager->m_ServiceParam.m_strLoginServiceIP
		+ "\",\"loginPort\":";
	memset(buf, 0, sizeof(buf));
	sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nLoginServicePort);	
	strRet += buf;
	strRet += ",\"messageIP\":\"" + m_pUserManager->m_ServiceParam.m_strMessageServiceIP
		+ "\",\"messagePort\":";
	sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nMessageServicePort);
	strRet += buf;
	strRet += ",\"chatIP\":\"" + m_pUserManager->m_ServiceParam.m_strChatServiceIP
		+ "\",\"chatPort\":";
	sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nChatServicePort);
	strRet += buf;
	strRet += ",\"uploadIP\":\"" + m_pUserManager->m_ServiceParam.m_strUploadServiceIP
		+ "\",\"uploadPort\":";
	sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nUploadServicePort);
	strRet += buf;
	strRet += ",\"downloadIP\":\"" + m_pUserManager->m_ServiceParam.m_strDownloadServiceIP
		+ "\",\"downloadPort\":";
	sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nDownloadServicePort);
	strRet += buf;
	strRet += ",\"voipIP\":\"" + m_pUserManager->m_ServiceParam.m_strVOIPServiceIP
		+ "\",\"voipPort\":";
	sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_nVOIPServicePort);
	strRet += buf;
	strRet += ",\"requestListAddr\":\"" + m_pUserManager->m_ServiceParam.m_strRequestListAddr + "\"";

	return strRet;
}

bool CLogin::logIn()
{
	bool bRet = false;
	if (m_pUserManager->m_bUserDispatch)
	{
		bRet = getAuthKey(m_pUserManager->m_ServiceParam.m_strUserId);
		if (bRet == false)
		{
			return bRet;
		}
		bRet = getToken(m_pUserManager->m_ServiceParam.m_strUserId, m_pUserManager->m_ServiceParam.m_strAgentId, m_pUserManager->m_strAuthKey);
		if (bRet == false)
		{
			return bRet;
		}
		bRet = getIMServerAddr(m_pUserManager->m_ServiceParam.m_strUserId, m_pUserManager->m_ServiceParam.m_strAgentId);
		if (bRet == false)
		{
			return bRet;
		}
	}
	else
	{
		bRet = true;
		m_pUserManager->m_strTokenId = "free";
		m_pUserManager->m_strIMServerIp = m_pUserManager->m_ServiceParam.m_strMessageServiceIP;
		m_pUserManager->m_nIMServerPort = m_pUserManager->m_ServiceParam.m_nMessageServicePort;
	}
	
	bRet = startIMServer((char*)m_pUserManager->m_strIMServerIp.c_str(), m_pUserManager->m_nIMServerPort, (char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(), (char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), (char*)m_pUserManager->m_strTokenId.c_str());
	return bRet;
}

/*
* 获取authKey
*/
bool CLogin::getAuthKey(string userId)
{
	bool bRet = false;
	m_pUserManager->m_strAuthKey = "";

	CString url = "";
	url.Format(_T("%s/authKey?userid=%s&appid=%s"), m_pUserManager->m_ServiceParam.m_strRequestListAddr.c_str(), userId.c_str(), m_pUserManager->m_ServiceParam.m_strAgentId.c_str());

	CString strPara = _T("");
	CString strContent;
	
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url, strPara, strContent);

	string str_json = strContent.GetBuffer(0);
	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素   
	{
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				m_pUserManager->m_strAuthKey = data.asCString();
				bRet = true;
			}
		}
	}
	return bRet;
}

/*
* 获取Token
*/
bool CLogin::getToken(string userId, string agentId, string authKey)
{
	bool bRet = false;
	m_pUserManager->m_strTokenId = "";

	CString url = "";
	url.Format(_T("http://%s:%d"), m_pUserManager->m_ServiceParam.m_strLoginServiceIP.c_str(), m_pUserManager->m_ServiceParam.m_nLoginServicePort);

	string strData = "userId=" + agentId + "_" + userId + "&authKey=" + authKey;
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
				m_pUserManager->m_strTokenId = data.asCString();
				bRet = true;
			}
		}
	}
	return bRet;
}

/*
* 通过调度获取IM服务地址
*/
bool CLogin::getIMServerAddr(string userId, string agentId)
{
	bool bRet = false;
	m_pUserManager->m_strIMServerIp = "";
	m_pUserManager->m_nIMServerPort = 0;
	CString url = "";
	url.Format(_T("http://%s:%d"), m_pUserManager->m_ServiceParam.m_strMessageServiceIP.c_str(), m_pUserManager->m_ServiceParam.m_nMessageServicePort);

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
				m_pUserManager->m_strIMServerIp = str.substr(0, pos);
				str = str.substr(pos + 1, str.length());
				m_pUserManager->m_nIMServerPort = atoi(str.c_str());
				printf("m_strIMServerIp:%s m_nIMServerPort:%d \n", m_pUserManager->m_strIMServerIp.c_str(), m_pUserManager->m_nIMServerPort);
				bRet = true;
			}
		}
	}
	return bRet;
}

/*
* 开启IM服务
*/
bool CLogin::startIMServer(string strIP, int nPort, string userId, string agentId, string strToken)
{
	return StarRtcCore::getStarRtcCoreInstance()->startIMServer((char*)strIP.c_str(), nPort, (char*)agentId.c_str(), (char*)userId.c_str(), (char*)strToken.c_str());
}
/*
* 停止IM服务
*/
bool CLogin::stopIMServer()
{
	return StarRtcCore::getStarRtcCoreInstance()->stopIMServer();
}

string CLogin::getUserManagerInfo()
{
	string strRet = "";
	string strUserDispatch = "1";
	if (m_pUserManager->m_bUserDispatch == false)
	{
		strUserDispatch = "0";
	}
	strRet = "\"authKey\":\"" + m_pUserManager->m_strAuthKey
		+ "\",\"dispatch\":" + strUserDispatch
		+ ",\"tokenId\":\"" + m_pUserManager->m_strTokenId + "\"," + getServiceParam();
	return strRet;
}
