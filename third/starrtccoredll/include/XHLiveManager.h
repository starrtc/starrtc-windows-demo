#pragma once
#include "CLiveManager.h"
#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif



class MATH_API XHLiveManager
{
public:
	XHLiveManager(ILiveManagerListener* pLiveListener);
	virtual ~XHLiveManager();
	static void addChatroomGetListListener(IChatroomGetListListener* pChatroomGetListListener);
	static void getLiveList(string strUserId, string listType);


	/**
	 * 设置媒体类型，音频和视频可以都打开，也可以单独打开一个。
	 * @param mediaTypeEnum 
	 */
	void setRtcMediaType(LIVE_MEDIA_TYPE mediaTypeEnum);

	/**
	 * 创建直播
	 */
	string createLive(string strName, int chatroomType, int channelType);

	/**
	 * 主播开始直播
	 * @param liveID 直播ID
	 */
	bool startLive(string liveID);

	/**
	 * 观众观看直播
	 * @param liveID 直播ID
	 */
	bool watchLive(string liveID);

	/**
	 * 观众申请连麦
	 * @param toID 主播的ID
	 */
	void applyToBroadcaster(string toID);

	/**
	 * 房主同意连麦
	 * @param toID 申请连麦者的ID
	 */
	void agreeApplyToBroadcaster(string toID);

	/**
	 * 房主拒绝连麦
	 * @param toID 申请连麦者的ID
	 */
	void refuseApplyToBroadcaster(string toID);

	/**
	 * 主播邀請连麦
	 * @param toID 被邀请人的ID
	 */
	void inviteToBroadcaster(string toID);

	/**
	 * 观众同意连麦
	 * @param toID 主播的ID
	 */
	void agreeInviteToBroadcaster(string toID);

	/**
	 * 观众拒绝连麦
	 * @param toID 主播的ID
	 */
	void refuseInviteToBroadcaster(string toID);

	/**
	 * 命令连麦者下麦
	 * @param toID 连麦者ID
	 */
	void commandToAudience(string toID);

	/**
	 * 离开直播
	 * @param callback 结果回调
	 */
	void leaveLive();

	/**
	 * 切换成大图
	 * @param userID 切换成大图的主播ID
	 */
	void changeToBig(string userID);

	/**
	 * 切换成小图
	 * @param userID 切换成小图的主播ID
	 */
	void changeToSmall(string userID);

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
	bool muteMember(string liveId, string memberID, int muteSeconds);

	/**
	 * 解除会议中某人的禁言
	 * @param meetingID 会议ID
	 * @param memberID 被禁言者ID
	 */
	bool unMuteMember(string liveId, string memberID);

	/**
	 * 从会议室踢出用户
	 * @param meetingID 会议ID
	 * @param memberID 被踢者ID
	 */
	bool kickMember(string liveId, string memberID);

	/**
	 * 保存到列表
	 * @param userId
	 * @param type
	 * @param liveId
	 * @param data
	 */
	bool saveToList(string userId, int type, string liveId, string data);

	/**
	 * 从列表删除
	 * @param userId 用户ID
	 * @param type 类型
	 * @param liveId liveID
	 */
	void deleteFromList(string userId, int type, string liveId);

	/**
	 * 推送RTMP流
	 * @param rtmpurl 推送地址
	 */
	void pushRtmp(string rtmpurl);

	/**
	 * 停止推送RTMP流
	 */
	void stopPushRtmp();

	/*
	 * 查询在线人数
	 */
	bool getOnlineNumber(string strLiveId);

	void insertAudioRaw(uint8_t* audioData, int dataLen);
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	void querySoundData(uint8_t** pData, int* nLength);
	void insertRealtimeData(uint8_t* realtimeData, int dataLen);
private:
	CLiveManager* m_pLiveManager;
};

