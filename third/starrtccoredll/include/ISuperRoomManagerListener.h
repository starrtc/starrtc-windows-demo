#pragma once
#include "CIMMessage.h"
class ISuperRoomManagerListener
{
public:
	/**
	 * 有新用户加入会议
	 * @param meetingID 会议ID
	 * @param userID 新加入者ID
	 */
	virtual void onJoined(string meetID, string userID) = 0;

	/**
	 * 有人离开会议
	 * @param meetingID 会议ID
	 * @param userID 离开者ID
	 */
	virtual void onLeft(string meetingID, string userID) = 0;

	/**
	 * 一些异常情况引起的出错，请在收到该回调后主动断开会议
	 * @param id 
	 * @param error 错误信息
	 */
	virtual void onError(string id, string error) = 0;


	/**
	 * 聊天室成员数变化
	 * @param number 变化后的会议人数
	 */
	virtual void onMembersUpdated(int number) = 0;

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfKicked() = 0;

	/**
	 * 自己被禁言
	 */
	virtual void onSelfMuted(int seconds) = 0;

	/**
	 * 连麦者的连麦被强制停止
	 * @param liveID 直播ID
	 */
	virtual void onCommandToStopPlay(string liveID) = 0;

	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(CIMMessage* pMessage) = 0;

	/**
	 * 收到私信消息
	 * @param message
	 */
	virtual void onReceivePrivateMessage(CIMMessage* pMessage) = 0;
	virtual int getRealtimeData(string strUserId, uint8_t* data, int len) = 0;
	/**
	 * 收到视频数据
	 * @param upId
	 * @param w 宽度
	 * @param h 高度
	 * @param videoData 数据
	 * @param videoDataLen 数据长度
	 */
	virtual int getVideoRaw(string strUserId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;
};