#pragma once
#include "IVdnManagerListener.h"
#include "CUserManager.h"
#include "CChatroomManager.h"
#include "ILiveInterface.h"
#include "ISrcManagerListener.h"

enum LIVE_VIDEO_TYPE
{
	LIVE_VIDEO_TYPE_GLOBAL_PUBLIC,		// 无需登录和验证
	LIVE_VIDEO_TYPE_LOGIN_PUBLIC,		// 需要登录，无需验证
	LIVE_VIDEO_TYPE_LOGIN_SPECIFY		// 需要登录和验证
};

enum MEETING_TYPE
{
	MEETING_TYPE_GLOBAL_PUBLIC,	// 无需登录和验证
	MEETING_TYPE_LOGIN_PUBLIC,	// 需要登录，无需验证
	MEETING_TYPE_LOGIN_SPECIFY	// 需要登录和验证
};

class CLiveManager
{
public:
	CLiveManager(CUserManager* pUserManager, IChatroomManagerListener* pChatroomManagerListener, IVdnManagerListener* pVdnManagerListener, ISrcManagerListener* pSrcManagerListener);
	virtual ~CLiveManager();
	bool createLiveAndJoin(string strName, int chatroomType, int channelType);

	/*
	 * 上报chatroom 和 channelID
	 */
	bool reportChatRoomAndChannel(string strName, string strChatroomId, string strChannelId);

	bool joinLive(string strChatroomId, string strChannelId, bool bSelfCreate);

	/*
	 * 设置数据流配置
	 */
	bool setStreamConfig(int* sendBuf, int length);
	bool closeLive();
	
public:
	IVdnManagerListener* m_pVdnManagerListener;
	ISrcManagerListener* m_pSrcManagerListener;
	CUserManager* m_pUserManager;
	CChatroomManager* m_pChatroomManager;
	ILiveInterface* m_pLiveInterface;
};

