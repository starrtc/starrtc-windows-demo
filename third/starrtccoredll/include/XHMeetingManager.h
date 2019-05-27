#pragma once
#include "CMeetingManager.h"
#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif
class MATH_API XHMeetingManager
{
public:
	XHMeetingManager(IMeetingManagerListener* pListener);
	virtual ~XHMeetingManager();
public:
	static void addChatroomGetListListener(IChatroomGetListListener* pChatroomGetListListener);
	static void getMeetingList();

	/**
	 * 设置媒体类型
	 * @param mediaTypeEnum 音视频同时存在，还是只开启其中一项。
	 */
	void setRtcMediaType(int mediaTypeEnum);

	/**
	 * 创建会议
	 * @param strName 名
	 * @param chatroomType chatroom类型
	  *@param channelType channel类型
	 */
	bool createMeeting(string strName, int chatroomType, int channelType);
	/**
	 * 加入会议
	 * @param strMeetingID 会议ID
	 */
	bool joinMeeting(string strMeetingID);

	/**
	 * 离开会议
	 * @param strMeetingID 会议ID
	 */
	bool leaveMeeting(string strMeetingID);

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
	bool muteMember(string meetingID, string memberID, int muteSeconds);

	/**
	 * 解除会议中某人的禁言
	 * @param meetingID 会议ID
	 * @param memberID 被禁言者ID
	 */
	bool unMuteMember(string meetingID, string memberID);

	/**
	 * 从会议室踢出用户
	 * @param meetingID 会议ID
	 * @param memberID 被踢者ID
	 */
	bool kickMember(string meetingID, string memberID);

	/**
	 * 保存到列表
	 * @param userId
	 * @param type
	 * @param meetingId
	 * @param data
	 */
	bool saveToList(string userId, int type, string meetingId, string data);

	/**
	 * 从列表删除
	 * @param userId 用户ID
	 * @param type 类型
	 * @param meetingId 会议室ID
	 */
	void deleteFromList(string userId, int type, string meetingId);

	/**
	 * 推送RTMP流
	 * @param rtmpurl 推送地址
	 */
	void pushRtmp(string rtmpurl);

	/**
	 * 停止推送RTMP流
	 */
	void stopPushRtmp();

	void insertAudioRaw(uint8_t* audioData, int dataLen);
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	void querySoundData(uint8_t** pData, int* nLength);
private:
	CMeetingManager* m_pMeetingManager;
};

