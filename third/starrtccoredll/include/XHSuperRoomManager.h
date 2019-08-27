#pragma once

#include "ISuperRoomManagerListener.h"
#include "IChatroomGetListListener.h"
#include "CIMMessage.h"
#include "CSuperRoomManager.h"
#include <string>
using namespace std;
#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif

class MATH_API XHSuperRoomManager
{
public:
	XHSuperRoomManager(ISuperRoomManagerListener* pListener);
	virtual ~XHSuperRoomManager();
public:
	static void addChatroomGetListListener(IChatroomGetListListener* pChatroomGetListListener);
	static void getSuperRoomList(string strUserId, string listType);

	/**
	 * 设置媒体类型，音频和视频可以都打开，也可以单独打开一个。
	 * @param mediaTypeEnum 
	 */
	void setRtcMediaType(LIVE_MEDIA_TYPE mediaTypeEnum);

	/**
	 * 创建超级对讲聊天室
	 * @param chatroomType chatroom类型
	 * @param channelType channelType类型
	 */
	string createSuperRoom(string strName, int chatroomType, int channelType);

	/**
	 * 加入超级聊天室
	 * @param roomID 直播ID
	 * @param callback 结果回调
	 */
	bool joinSuperRoom(string roomID);

	/**
	 *  停止发言
	 *  @param callback 结果回调
	 */
	void layDownMic();

	/**
	 * 申请发言
	 * @param callback 结果回调
	 */
	bool pickUpMic();

	/**
	 * 离开聊天室
	 * @param callback 结果回调
	 */
	void leaveSuperRoom();

	/**
	* 命令连麦者下麦
	* @param toID 连麦者ID
	*/
	void commandToAudience(string toID);

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
	void setAudioEnable(bool enable);

	/**
	 * 动态开关视频，直播过程中可随时开关视频，直播结束后状态自动重置。
	 */
	void setVideoEnable(bool enable);

	/**
	 * 发送超级对讲消息
	 * @param message 发送的消息内容
	 * @param callback 结果回调
	 * @return 返回发送的消息对象
	 */
	CIMMessage* sendMessage(string strMessage);

	/**
	 * 发送超级对讲私密消息
	 * 私密消息只有目标用户可以收到
	 * @param toID 目标用户ID
	 * @param message 发送的消息内容
	 * @return 返回发送的消息对象
	 */
	CIMMessage* sendPrivateMessage(string toID, string strMessage);

	/**
	 * 对会议中的某人禁言
	 * @param strSuperRoomId 会议ID
	 * @param memberID 被禁言者ID
	 * @param muteSeconds 禁言时间
	 * @param callback 结果回调
	 */
	bool muteMember(string strSuperRoomId, string memberID, int muteSeconds);

	/**
	 * 解除超级对讲中某人的禁言
	 * @param meetingID 会议ID
	 * @param memberID 被禁言者ID
	 */
	bool unMuteMember(string strSuperRoomId, string memberID);

	/**
	 * 从超级对讲踢出用户
	 * @param meetingID 会议ID
	 * @param memberID 被踢者ID
	 */
	bool kickMember(string strSuperRoomId, string memberID);

	/**
	 * 保存到列表
	 * @param userId
	 * @param type
	 * @param meetingId
	 * @param data
	 */
	bool saveToList(string userId, int type, string meetingId, string data);

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
	void insertRealtimeData(uint8_t* realtimeData, int dataLen);

	/*
	 * 查询在线人数
	 */
	bool getOnlineNumber(string strLiveId);
private:
	CSuperRoomManager* m_pSuperRoomManager;
};

