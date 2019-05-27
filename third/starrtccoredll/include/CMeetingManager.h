#pragma once
#include "ISrcManagerListener.h"
#include "IMeetingManagerListener.h"
#include "CUserManager.h"
#include "CChatroomManager.h"
#include "CSrcManager.h"
#include <map>
enum MEETING_TYPE
{
	MEETING_TYPE_GLOBAL_PUBLIC,	// 无需登录和验证
	MEETING_TYPE_LOGIN_PUBLIC,	// 需要登录，无需验证
	MEETING_TYPE_LOGIN_SPECIFY	// 需要登录和验证
};



class CMeetingManager: public IChatroomManagerListener, public ISrcManagerListener
{
public:
	CMeetingManager(CUserManager* pUserManager, IMeetingManagerListener* pListener);
	virtual ~CMeetingManager();
public:
	static void addChatroomGetListListener(IChatroomGetListListener* pChatroomGetListListener);
	static void getMeetingList(CUserManager* pUserManager);
	bool createMeeting(string strName, int chatroomType, int channelType);
	void insertAudioRaw(uint8_t* audioData, int dataLen);
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);

	/*
	 * 上报chatroom 和 channelID
	 */
	bool reportChatRoomAndChannel(string strName, string strChatroomId, string strChannelId);
	bool joinChatroom(string strChatroomId);
	bool join(string strChatroomId, string strChannelId);
	bool closeChatroom();

	bool closeLive();

	bool close();

	/**
	 * 切换成大图
	 * @param strUserID 切换成大图的用户ID
	 */
	bool changeToBig(string strUserID);

	/**
	 * 切换成小图
	 * @param userID 切换成小图的用户ID
	 */
	bool changeToSmall(string strUserID);

	/**
	 * 动态开关音频，直播过程中可随时开关音频，直播结束后状态自动重置。
	 */
	void setAudioEnable(bool bEnable);

	/**
	 * 动态开关视频，直播过程中可随时开关视频，直播结束后状态自动重置。
	 */
	void setVideoEnable(bool bEnable);
	/**
	 * 发送会议消息
	 * @param message 发送的消息内容
	 * @param callback 结果回调
	 * @return 返回发送的消息对象
	 */
	CIMMessage* sendMessage(string strMessage);

	/**
	 * 发送会议私密消息
	 * 私密消息只有目标用户可以收到
	 * @param toID 目标用户ID
	 * @param message 发送的消息内容
	 * @return 返回发送的消息对象
	 */
	CIMMessage* sendPrivateMessage(string toID, string strMessage);

	/**
	 * 对会议中的某人禁言
	 * @param meetingID 会议ID
	 * @param memberID 被禁言者ID
	 * @param muteSeconds 禁言时间
	 * @param callback 结果回调
	 */
	bool muteMember(string strChatRoomId, string memberID, int muteSeconds);

	/**
	 * 解除会议中某人的禁言
	 * @param meetingID 会议ID
	 * @param memberID 被禁言者ID
	 */
	bool unMuteMember(string strChatRoomId, string memberID);

	/**
	 * 从会议室踢出用户
	 * @param meetingID 会议ID
	 * @param memberID 被踢者ID
	 */
	bool kickMember(string strChatRoomId, string memberID);

	bool applyToBroadcaster(string chatroomId, string channelId, string toId);

	void agreeApplyToBroadcaster(string toId);

	void refuseApplyToBroadcaster(string toId);

	void inviteToBroadcaster(string toId);

	void agreeInviteToBroadcaster(string toId);

	void refuseInviteToBroadcaster(string toId);
	void querySoundData(uint8_t** pData, int* nLength);
public:
	/**
	 * 聊天室成员数变化
	 * @param number
	 */
	virtual void onMembersUpdated(int number);

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfKicked();

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfMuted(int seconds);

	/**
	 * 聊天室已关闭
	 */
	virtual void onClosed();

	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(CIMMessage* pMessage);

	/**
	 * 收到私信消息
	 * @param message
	 */
	virtual void onReceivePrivateMessage(CIMMessage* pMessage);
public:
	//src
	virtual int uploaderAddSrc(char* upUserId, int upId);
	virtual int uploaderRemoveSrc(char* upUserId, int upId);
	virtual int getRealtimeDataSrc(int upId, uint8_t* data, int len);
	virtual int getVideoRawSrc(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	virtual int deleteChannel(char* channelId);
	virtual int stopOK();
	virtual int srcError(char* errString);

public:
	static IChatroomGetListListener* m_pChatroomGetListListener;
	IMeetingManagerListener* m_pMeetingManagerListener;
	CUserManager* m_pUserManager;
	CChatroomManager* m_pChatroomManager;
	CSrcManager* m_pSrcManager;
	

	map<int, StarLiveUserInfo> m_StarLiveUserInfo;
};

