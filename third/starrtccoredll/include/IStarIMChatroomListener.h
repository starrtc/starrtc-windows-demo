#pragma once
#include "CIMMessage.h"
#include "ChatroomInfo.h"
#include <list>
using namespace std;
class IStarIMChatroomListener
{
public:
	//聊天室创建成功
	virtual void chatroomCreateOK(string roomId, int maxContentLen) = 0;
	//聊天室加入成功
	virtual void chatroomJoinOK(string roomId, int maxContentLen) = 0;
	//聊天室创建失败
	virtual void chatroomCreateFailed(string errString) = 0;
	//聊天室加入失败
	virtual void chatroomJoinFailed(string roomId, string errString) = 0;
	//聊天室报错
	virtual void chatRoomErr(string errString) = 0;
	//聊天室关闭成功
	virtual void chatroomStopOK() = 0;
	//查询聊天室列表回调
	virtual int chatroomQueryAllListOK(list<ChatroomInfo>& chatRoomInfoList) = 0;
	//聊天室删除成功
	virtual void chatroomDeleteOK(string roomId) = 0;
	//聊天室删除失败
	virtual void chatroomDeleteFailed(string roomId, string errString) = 0;
	//聊天室禁言成功
	virtual void chatroomBanToSendMsgOK(string banUserId, int banTime) = 0;
	//聊天室禁言失败
	virtual void chatroomBanToSendMsgFailed(string banUserId, int banTime, string errString) = 0;
	//聊天室踢人成功
	virtual void chatroomKickOutOK(string kickOutUserId) = 0;
	//聊天余额不足
	virtual void chatroomSendMsgNoFee() = 0;
	//聊天室踢人失败
	virtual void chatroomKickOutFailed(string kickOutUserId, string errString) = 0;
	//聊天室 自己被禁言
	virtual void chatroomSendMsgBanned(int remainTimeSec) = 0;
	//聊天室 自己被踢出
	virtual void chatroomKickedOut() = 0;
	//聊天室 收到消息
	virtual void chatroomGetNewMsg(CIMMessage* pMsg) = 0;
	//聊天室 收到私信消息
	virtual void chatroomGetNewPrivateMsg(CIMMessage* pMsg) = 0;
	//聊天室在线人数
	virtual void getRoomOnlineNumber(string roomId, int number) = 0;
	//聊天室在线人数
	virtual void sendMessageSuccess(int msgIndx) = 0;
	//聊天室在线人数
	virtual void sendMessageFailed(int msgIndx) = 0;
	//收到控制消息
	virtual void revControlMessage(string fromID, int code) = 0;
};
