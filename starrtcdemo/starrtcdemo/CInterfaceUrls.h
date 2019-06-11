#pragma once
#include <string>
#include <list>
#include "ChatroomInfo.h"
#include "CGroupInfo.h"
#include "CUserManager.h"

using namespace std;
class CInterfaceUrls
{
public:
	CInterfaceUrls();
	virtual ~CInterfaceUrls();
	static void setBaseUrl(string baseUrl);
	//会议室列表
	static void demoRequestMeetingList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//小班课列表
	static void demoRequestMiniClassList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//聊天室列表
	static void demoRequestChatroomList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//群列表
	static void demoRequestGroupList(list<CGroupInfo>& retGroupList, CUserManager* pUserManager);
	//群成员列表
	static void demoRequestGroupMembers(string groupId, CUserManager* pUserManager, list<string>& userList);
	//在线用户列表
	static void demoRequestOnlineUsers(CUserManager* pUserManager, list<string>& userList);
	//互动直播列表
	static void demoRequestLiveList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//音频直播列表
	static void demoRequestAudioLiveList(list<ChatroomInfo>& listData, CUserManager* pUserManager);
	//互动直播
	static void demoReportLive(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
	//上报语音直播
	static void demoReportAudioLive(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
	//上报小班课
	static void demoReportMiniClass(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
	//会议室
	static void demoReportMeeting(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
	//聊天室
	static void demoReportChatroom(string liveID, string liveName, string creatorID, CUserManager* pUserManager);
public:
	static string BASE_URL;
	//获取authKey
	static string LOGIN_URL;
	//会议室列表
	static string MEETING_LIST_URL;
	//直播列表
	static string LIVE_LIST_URL;
	//音频直播列表
	static string AUDIO_LIVE_LIST_URL;
	//小班课列表
	static string MINI_CLASS_LIST_URL;
	//上报直播间使用的聊天室ID（直播里的文字聊天用了一个聊天室）
	static string LIVE_SET_CHAT_URL;
	//聊天室列表
	static string CHATROOM_LIST_URL;
	//自己加入的群列表
	static string GROUP_LIST_URL;
	//群成员列表
	static string GROUP_MEMBERS_URL;
	//在线用户列表
	static string ONLINE_USER_LIST_URL;

	//上报直播
	static string REPORT_LIVE_INFO_URL;
	//上报语音直播
	static string REPORT_AUDIO_LIVE_INFO_URL;
	//上报小班课
	static string REPORT_MINI_CLASS_INFO_URL;
	//上报会议
	static string REPORT_MEETING_INFO_URL;
	//上报聊天室
	static string REPORT_CHATROOM_INFO_URL;
};

