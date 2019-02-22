#include "stdafx.h"
#include "CLogin.h"
#include "json.h"

#include "HttpClient.h"
#include "StarRtcCore.h"
CLogin::CLogin(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
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

		::GetPrivateProfileString("param", "agentId", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strAgentId = buf;
		::GetPrivateProfileString("param", "loginService", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strLoginServiceIP = buf;
		::GetPrivateProfileString("param", "messageSercive", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strMessageServiceIP = buf;
		::GetPrivateProfileString("param", "chatSercive", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strChatServiceIP = buf;
		::GetPrivateProfileString("param", "uploadSercive", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strUploadServiceIP = buf;
		::GetPrivateProfileString("param", "downloadSercive", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strDownloadServiceIP = buf;
		::GetPrivateProfileString("param", "voipSercive", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strVOIPServiceIP = buf;
		::GetPrivateProfileString("param", "requestListAddr", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_strRequestListAddr = buf;

		::GetPrivateProfileString("param", "bigPicWidth", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_BigPic.m_nWidth = atoi(buf);

		::GetPrivateProfileString("param", "bigPicHeight", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_BigPic.m_nHeight = atoi(buf);

		::GetPrivateProfileString("param", "smallPicWidth", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_SmallPic.m_nWidth = atoi(buf);

		::GetPrivateProfileString("param", "smallPicHeight", "", buf, sizeof(buf), strPath.c_str());
		m_pUserManager->m_ServiceParam.m_SmallPic.m_nHeight = atoi(buf);
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
		::WritePrivateProfileString("param", "userId", m_pUserManager->m_ServiceParam.m_strUserId.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "agentId", m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "loginService", m_pUserManager->m_ServiceParam.m_strLoginServiceIP.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "messageSercive", m_pUserManager->m_ServiceParam.m_strMessageServiceIP.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "chatSercive", m_pUserManager->m_ServiceParam.m_strChatServiceIP.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "uploadSercive", m_pUserManager->m_ServiceParam.m_strUploadServiceIP.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "downloadSercive", m_pUserManager->m_ServiceParam.m_strDownloadServiceIP.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "voipSercive", m_pUserManager->m_ServiceParam.m_strVOIPServiceIP.c_str(), strPath.c_str());
		::WritePrivateProfileString("param", "requestListAddr", m_pUserManager->m_ServiceParam.m_strRequestListAddr.c_str(), strPath.c_str());


		char buf[128] = { 0 };
		//_itoa(m_BigPic.m_nWidth, buf, 10);
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_BigPic.m_nWidth);
		::WritePrivateProfileString("param", "bigPicWidth", buf, strPath.c_str());

		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_BigPic.m_nHeight);
		::WritePrivateProfileString("param", "bigPicHeight", buf, strPath.c_str());

		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_SmallPic.m_nWidth);
		::WritePrivateProfileString("param", "smallPicWidth", buf, strPath.c_str());

		memset(buf, 0, sizeof(buf));
		sprintf_s(buf, "%d", m_pUserManager->m_ServiceParam.m_SmallPic.m_nHeight);
		::WritePrivateProfileString("param", "smallPicHeight", buf, strPath.c_str());
	}
	return true;
}

string CLogin::getServiceParam()
{
	string strRet = "";

	strRet = "\"userId\":\"" + m_pUserManager->m_ServiceParam.m_strUserId
		+ "\",\"agentId\":\"" + m_pUserManager->m_ServiceParam.m_strAgentId
		+ "\",\"loginIP\":\"" + m_pUserManager->m_ServiceParam.m_strLoginServiceIP
		+ "\",\"messageIP\":\"" + m_pUserManager->m_ServiceParam.m_strMessageServiceIP
		+ "\",\"chatIP\":\"" + m_pUserManager->m_ServiceParam.m_strChatServiceIP
		+ "\",\"uploadIP\":\"" + m_pUserManager->m_ServiceParam.m_strUploadServiceIP
		+ "\",\"downloadIP\":\"" + m_pUserManager->m_ServiceParam.m_strDownloadServiceIP
		+ "\",\"voipIP\":\"" + m_pUserManager->m_ServiceParam.m_strVOIPServiceIP + "\"";

	return strRet;
}

bool CLogin::logIn()
{
	bool bRet = getAuthKey(m_pUserManager->m_ServiceParam.m_strUserId);
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
	url.Format(_T("https://%s/public/authKey?userid=%s&appid=%s"), "api.starrtc.com", userId.c_str(), m_pUserManager->m_ServiceParam.m_strAgentId.c_str());

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
	url.Format(_T("http://%s:9920"), m_pUserManager->m_ServiceParam.m_strLoginServiceIP.c_str());

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
	url.Format(_T("http://%s:9904"), m_pUserManager->m_ServiceParam.m_strMessageServiceIP.c_str());

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
	return StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->startIMServer();
}
/*
* 开启IM服务
*/
bool CLogin::stopIMServer()
{
	return StarRtcCore::getStarRtcCoreInstance(m_pUserManager)->stopIMServer();
}

string CLogin::getUserManagerInfo()
{
	string strRet = "";
	strRet = "\"authKey\":\"" + m_pUserManager->m_strAuthKey
		+ "\",\"tokenId\":\"" + m_pUserManager->m_strTokenId + "\"," + getServiceParam();
	return strRet;
}
