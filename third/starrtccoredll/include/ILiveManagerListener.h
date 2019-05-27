#pragma once
#include "CIMMessage.h"
class ILiveManagerListener
{
public:
	/**
	 * 有主播加入
	 * @param liveID 直播ID
	 * @param actorID 新加入的主播ID
	 */
	virtual void onActorJoined(string liveID, string actorID) = 0;

	/**
	 * 有主播离开
	 * @param liveID 直播ID
	 * @param actorID 离开的主播ID
	 */
	virtual void onActorLeft(string liveID, string actorID) = 0;

	/**
	 * 房主收到其他用户的连麦申请
	 * @param liveID
	 * @param applyUserID
	 */
	virtual void onApplyBroadcast(string liveID, string applyUserID) = 0;

	/**
	 * 申请连麦用户收到的回复
	 * @param liveID
	 * @param result
	 */
	virtual void onApplyResponsed(string liveID, bool bAgree) = 0;

	/**
	* 普通用户收到连麦邀请
	* @param liveID 直播ID
	* @param applyUserID 发出邀请的人的ID（主播ID）
	*/
	virtual void onInviteBroadcast(string liveID, string applyUserID) = 0;

	/**
	 * 主播收到的邀请连麦结果
	 * @param liveID 直播ID
	 * @param result 邀请结果
	 */
	virtual void onInviteResponsed(string liveID) = 0;

	/**
	 * 一些异常情况引起的出错，请在收到该回调后主动断开直播
	 * @param liveID 直播ID
	 * @param error 错误信息
	 */
	virtual void onLiveError(string liveID, string error) = 0;

	/**
	 * 聊天室成员数变化
	 * @param number
	 */
	virtual void onMembersUpdated(int number) = 0;

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfKicked() = 0;

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfMuted(int seconds) = 0;

	/**
	 * 连麦者的连麦被强制停止
	 * @param liveID 直播ID
	 */
	virtual void onCommandToStopPlay(string  liveID) = 0;

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
	virtual int getVideoRaw(string strUserId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;
};