#include "stdafx.h"
#include "CInterfaceUrls.h"
#include "HttpClient.h"
#include "json.h"

string CInterfaceUrls::BASE_URL = "";
//获取authKey
string CInterfaceUrls::LOGIN_URL = "";
//会议室列表
string CInterfaceUrls::MEETING_LIST_URL = "";
//直播列表
string CInterfaceUrls::LIVE_LIST_URL = "";
//音频直播列表
string CInterfaceUrls::AUDIO_LIVE_LIST_URL = "";
//小班课列表
string CInterfaceUrls::MINI_CLASS_LIST_URL = "";
//上报直播间使用的聊天室ID（直播里的文字聊天用了一个聊天室）
string CInterfaceUrls::LIVE_SET_CHAT_URL = "";
//聊天室列表
string CInterfaceUrls::CHATROOM_LIST_URL = "";
//自己加入的群列表
string CInterfaceUrls::GROUP_LIST_URL = "";
//群成员列表
string CInterfaceUrls::GROUP_MEMBERS_URL = "";
//在线用户列表
string CInterfaceUrls::ONLINE_USER_LIST_URL = "";

//上报直播
string CInterfaceUrls::REPORT_LIVE_INFO_URL = "";
//上报语音直播
string CInterfaceUrls::REPORT_AUDIO_LIVE_INFO_URL = "";
//上报小班课
string CInterfaceUrls::REPORT_MINI_CLASS_INFO_URL = "";
//上报会议
string CInterfaceUrls::REPORT_MEETING_INFO_URL = "";
//上报聊天室
string CInterfaceUrls::REPORT_CHATROOM_INFO_URL = "";


//UTF8转ANSI
string CInterfaceUrls::UTF8toANSI(string strUTF8)
{
	string retStr = "";
	//获取转换为多字节后需要的缓冲区大小，创建多字节缓冲区
	UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(CP_UTF8, NULL, strUTF8.c_str(), -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;

	nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;

	retStr = szBuffer;
	//清理内存
	delete[]szBuffer;
	delete[]wszBuffer;
	return retStr;
}
//ANSI转UTF8
string CInterfaceUrls::ANSItoUTF8(string strAnsi)
{
	string retStr = "";
	//获取转换为宽字节后需要的缓冲区大小，创建宽字节缓冲区，936为简体中文GB2312代码页
	UINT nLen = MultiByteToWideChar(936, NULL, strAnsi.c_str(), -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(936, NULL, strAnsi.c_str(), -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;
	//获取转为UTF8多字节后需要的缓冲区大小，创建多字节缓冲区
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(CP_UTF8, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;

	retStr = szBuffer;
	//内存清理
	delete[]wszBuffer;
	delete[]szBuffer;
	return retStr;
}

CInterfaceUrls::CInterfaceUrls()
{
}


CInterfaceUrls::~CInterfaceUrls()
{
}

unsigned char CInterfaceUrls::ToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

unsigned char CInterfaceUrls::FromHex(unsigned char x)
{
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else
	{
	}
	return y;
}

std::string CInterfaceUrls::UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] % 16);
		}
	}
	return strTemp;
}

std::string CInterfaceUrls::UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+') strTemp += ' ';
		else if (str[i] == '%')
		{
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
}

void CInterfaceUrls::demoSaveToList(string userId, int listType, string id, string data)
{
	string url = "http://www.starrtc.com/aec/list/save.php";
	url = url + "?userId=" + userId + "&listType=";
	char buf[256] = { 0 };
	sprintf_s(buf, "%d", listType);
	url = url + buf;
	url = url + "&roomId=" + id;

	data = CInterfaceUrls::ANSItoUTF8(data);
	data = CInterfaceUrls::UrlEncode(data);

	url = url + "&data=" + data;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}

void CInterfaceUrls::demoDeleteFromList(string userId, int listType, string id)
{
	string url = "http://www.starrtc.com/aec/list/del.php";
	url = url + "?userId=" + userId + "&listType=";
	char buf[256] = { 0 };
	sprintf_s(buf, "%d", listType);
	url = url + buf;
	url = url + "&roomId=" + id;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}

void CInterfaceUrls::demoQueryList(string listType, list<ChatroomInfo>& listData)
{
	string url = "http://www.starrtc.com/aec/list/query.php";

	string strData = "listTypes=";
	strData = strData + listType;


	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);

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
					if (data[i].isMember("data"))
					{
						string strVal = data[i].get("data", "").asCString();
						

						strVal = CInterfaceUrls::UrlDecode(strVal);
						strVal = CInterfaceUrls::UTF8toANSI(strVal);
						Json::Reader reader1;
						Json::Value root1;
						if (strVal != "" && reader1.parse(strVal, root1))
						{
							ChatroomInfo chatroomInfo;
							if (root1.isMember("id"))
							{
								chatroomInfo.m_strRoomId = root1["id"].asCString();
							}
							if (root1.isMember("name"))
							{
								chatroomInfo.m_strName = root1["name"].asCString();
							}
							if (root1.isMember("creator"))
							{
								chatroomInfo.m_strCreaterId = root1["creator"].asCString();
							}
							listData.push_back(chatroomInfo);
						}
					}
				}
			}
		}
	}
}

void CInterfaceUrls::demoQueryImGroupList(string userId, list<CGroupInfo>& groupInfoList)
{
	string url = "http://www.starrtc.com/aec/group/list.php";

	string strData = "userId=";
	strData = strData + userId;


	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);

	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素   
	{
		//{"status":1,"data":[{"groupName":"\u5403\u918b","creator":"448999","groupId":"100391"}]}
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				int nSize = data.size();
				for (int i = 0; i < nSize; i++)
				{
					CGroupInfo groupInfo;
					if (data[i].isMember("groupName"))
					{
						groupInfo.m_strName = CInterfaceUrls::UrlDecode(data[i]["groupName"].asCString());
					}

					if (data[i].isMember("groupId"))
					{
						groupInfo.m_strId = data[i]["groupId"].asCString();
					}

					if (data[i].isMember("creator"))
					{
						groupInfo.m_strCreaterId = data[i]["creator"].asCString();
					}
					groupInfoList.push_back(groupInfo);
				}
			}
		}
	}
}

void CInterfaceUrls::demoQueryImGroupInfo(string userId, string groupId, CGroupMemoryInfo& userList)
{
	string url = "http://www.starrtc.com/aec/group/members.php";

	string strData = "userId=";
	strData = strData + userId+ "&groupId=" + groupId;


	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);

	string str_json = strContent.GetBuffer(0);

	Json::Reader reader;
	Json::Value root;
	if (nRet == 0 && str_json != "" && reader.parse(str_json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素   
	{
		//{"status":1,"data":{"userIdList":"448999","isIgnore":"0"}}
		if (root.isMember("status") && root["status"].asInt() == 1)
		{
			if (root.isMember("data"))
			{
				Json::Value data = root.get("data", "");
				if (data.isMember("userIdList"))
				{
					string strUserIdList = data["userIdList"].asCString();
					while (strUserIdList != "")
					{
						string strInfo = strUserIdList;
						int pos = strUserIdList.find(",");
						if (pos > 0)
						{
							strInfo = strUserIdList.substr(0, pos);
							strUserIdList = strUserIdList.substr(pos + 1, strUserIdList.length() - pos - 1);
						}
						else
						{
							strUserIdList = "";
						}
						userList.m_UserIdList.push_back(strInfo);
					}
				}
				if (data.isMember("isIgnore"))
				{
					string strIngore = data["isIgnore"].asCString();
					if (strIngore == "1")
					{
						userList.m_bIgnore = true;
					}
					else
					{
						userList.m_bIgnore = false;
					}
				}
				
			}
		}
	}
}

void CInterfaceUrls::setBaseUrl(string baseUrl)
{
	BASE_URL = baseUrl;
	LOGIN_URL = BASE_URL + "/authKey";
	MEETING_LIST_URL = BASE_URL + "/meeting/list";
	LIVE_LIST_URL = BASE_URL + "/live/list";
	AUDIO_LIVE_LIST_URL = BASE_URL + "/audio/list";
	MINI_CLASS_LIST_URL = BASE_URL + "/class/list";
	LIVE_SET_CHAT_URL = BASE_URL + "/live/set_chat";
	CHATROOM_LIST_URL = BASE_URL + "/chat/list";
	GROUP_LIST_URL = BASE_URL + "/group/list_all";
	ONLINE_USER_LIST_URL = BASE_URL + "/user/list";
	GROUP_MEMBERS_URL = BASE_URL + "/group/members";
	REPORT_LIVE_INFO_URL = BASE_URL + "/live/store";
	REPORT_AUDIO_LIVE_INFO_URL = BASE_URL + "/audio/store";
	REPORT_MINI_CLASS_INFO_URL = BASE_URL + "/class/store";
	REPORT_MEETING_INFO_URL = BASE_URL + "/meeting/store";
	REPORT_CHATROOM_INFO_URL = BASE_URL + "/chat/store";
}

void CInterfaceUrls::demoRequestMeetingList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(MEETING_LIST_URL.c_str(), strData.c_str(), strContent);

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
					ChatroomInfo chatroomInfo;
					if (data[i].isMember("Name"))
					{
						chatroomInfo.m_strName = data[i]["Name"].asCString();
					}

					if (data[i].isMember("ID"))
					{
						chatroomInfo.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Creator"))
					{
						chatroomInfo.m_strCreaterId = data[i]["Creator"].asCString();
					}
					listData.push_back(chatroomInfo);
				}
			}
		}
	}
}
void CInterfaceUrls::demoRequestMiniClassList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + "stargWeHN8Y7";

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(MINI_CLASS_LIST_URL.c_str(), strData.c_str(), strContent);
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
					ChatroomInfo chatroomInfo;
					if (data[i].isMember("Name"))
					{
						chatroomInfo.m_strName = data[i]["Name"].asCString();
					}

					if (data[i].isMember("ID"))
					{
						chatroomInfo.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Creator"))
					{
						chatroomInfo.m_strCreaterId = data[i]["Creator"].asCString();
					}
					listData.push_back(chatroomInfo);
				}
			}
		}
	}
}

//聊天室列表
void CInterfaceUrls::demoRequestChatroomList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(CHATROOM_LIST_URL.c_str(), strData.c_str(), strContent);
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
					ChatroomInfo chatroomInfo;
					if (data[i].isMember("Creator"))
					{
						chatroomInfo.m_strCreaterId = data[i]["Creator"].asCString();
					}

					if (data[i].isMember("ID"))
					{
						chatroomInfo.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Name"))
					{
						chatroomInfo.m_strName = data[i]["Name"].asCString();
					}
					listData.push_back(chatroomInfo);
				}
			}
		}
	}
}
//群列表
void CInterfaceUrls::demoRequestGroupList(list<CGroupInfo>& retGroupList, CUserManager* pUserManager)
{
	retGroupList.clear();
	string strData = "userid=";
	strData = strData + pUserManager->m_ServiceParam.m_strUserId.c_str() + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(GROUP_LIST_URL.c_str(), strData.c_str(), strContent);
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
}

//群成员列表
void CInterfaceUrls::demoRequestGroupMembers(string groupId, CUserManager* pUserManager, list<string>& userList)
{
	userList.clear();
	string strData = "groupId=";
	strData = strData + groupId.c_str() + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(GROUP_MEMBERS_URL.c_str(), strData.c_str(), strContent);
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
}
//在线用户列表
void CInterfaceUrls::demoRequestOnlineUsers(CUserManager* pUserManager, list<string>& userList)
{
	userList.clear();

	string strData = "appid=";
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(ONLINE_USER_LIST_URL.c_str(), strData.c_str(), strContent);
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
}

//互动直播列表
void CInterfaceUrls::demoRequestLiveList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + pUserManager->m_ServiceParam.m_strAgentId.c_str();
	std::string strErrInfo = "";

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(LIVE_LIST_URL.c_str(), strData.c_str(), strContent);
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
					ChatroomInfo livePro;

					if (data[i].isMember("ID"))
					{
						livePro.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Name"))
					{
						livePro.m_strName = data[i]["Name"].asCString();
					}

					if (data[i].isMember("Creator"))
					{
						livePro.m_strCreaterId = data[i]["Creator"].asCString();
					}

					listData.push_back(livePro);
				}
			}
		}
	}
}

//音频直播列表
void CInterfaceUrls::demoRequestAudioLiveList(list<ChatroomInfo>& listData, CUserManager* pUserManager)
{
	listData.clear();
	string strData = "appid=";
	strData = strData + "stargWeHN8Y7";

	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(AUDIO_LIVE_LIST_URL.c_str(), strData.c_str(), strContent);
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
					ChatroomInfo livePro;

					if (data[i].isMember("ID"))
					{
						livePro.m_strRoomId = data[i]["ID"].asCString();
					}

					if (data[i].isMember("Name"))
					{
						livePro.m_strName = data[i]["Name"].asCString();
					}

					if (data[i].isMember("Creator"))
					{
						livePro.m_strCreaterId = data[i]["Creator"].asCString();
					}
					if (data[i].isMember("liveState"))
					{
						string strStatus = data[i]["liveState"].asCString();
						if (strStatus == "1")
						{
							livePro.m_bLive = true;
						}
						else
						{
							livePro.m_bLive = false;
						}
					}
					

					listData.push_back(livePro);
				}
			}
		}
	}
}

//互动直播
void CInterfaceUrls::demoReportLive(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_LIVE_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}

//上报语音直播
void CInterfaceUrls::demoReportAudioLive(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_AUDIO_LIVE_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + "stargWeHN8Y7";
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);

}
//上报小班课
void CInterfaceUrls::demoReportMiniClass(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_MINI_CLASS_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + "stargWeHN8Y7";
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}
//会议室
void CInterfaceUrls::demoReportMeeting(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_MEETING_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}
//聊天室
void CInterfaceUrls::demoReportChatroom(string liveID, string liveName, string creatorID, CUserManager* pUserManager)
{
	string url = REPORT_CHATROOM_INFO_URL + "?ID=" + liveID + "&Name=" + liveName + "&Creator=" + creatorID + "&appid=" + pUserManager->m_ServiceParam.m_strAgentId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";
	string str_json = "";
	CString strContent = "";
	CHttpClient httpClient;
	int nRet = httpClient.HttpPost(url.c_str(), strData.c_str(), strContent);
}
