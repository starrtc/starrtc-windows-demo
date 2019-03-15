#pragma once
#include "IChatroomManagerListener.h"
#include "IStarIMChatroomListener.h"
#include "CUserManager.h"
#include <string>
using namespace std;

enum CHATROOM_TYPE
{
	CHATROOM_TYPE_UNABLE,	// 占位
	CHATROOM_TYPE_PUBLIC,	// 无需登录和验证
	CHATROOM_TYPE_LOGIN		// 需要登录，无需验证
};

class CChatroomManager : public IStarIMChatroomListener
{
public:
	CChatroomManager(CUserManager* pUserManager, IChatroomManagerListener* pChatroomManagerListener);
	~CChatroomManager();
public:
	void resetReturnVal();
	/*
	 * 设置chatroom id
	 */
	void setChatroomId(string chatRoomId);

	/*
	 * 通过调度获取ChatRoom服务地址
	 */
	bool getChatRoomServerAddr();

	/*
	 * 创建ChatRoom
	 */
	bool createChatRoom(string strName, int chatroomType);

	/*
	 * 加入ChatRoom
	 */
	bool joinChatRoom();
	/*
	 * 查询chatroom在线人数
	 */
	bool getOnlineNumber(string strChatroomId);

	bool banToSendMsg(char* banUserId, int banTime);
	bool kickOutUser(char* kickOutUserId);
	bool sendChat(CIMMessage* pIMMessage);
	bool sendPrivateChat(string toUserId, char* msgData);
	bool sendChatroomPrivateControlMessage(string targetId, int code);
	bool deleteChatRoom();

	bool reportChatroom(string strName, string strRoomId);

	/*
	 *  与ChatRoom断开连接
	 */
	bool stopChatRoomConnect();

	bool exit();

public:
	/**
	 * 聊天室创建成功
	 */
	virtual void chatroomCreateOK(string roomId, int maxContentLen);

	/**
	 * 聊天室加入成功
	 */
	virtual void chatroomJoinOK(string roomId, int maxContentLen);

	/**
	 * 聊天室创建失败
	 */
	virtual void chatroomCreateFailed(string errString);

	/**
	 * 聊天室加入失败
	 */
	virtual void chatroomJoinFailed(string roomId, string errString);

	/**
	 * 聊天室报错
	 */
	virtual void chatRoomErr(string errString);

	/**
	 * 聊天室关闭成功
	 */
	virtual void chatroomStopOK();

	/**
	 * 聊天室删除成功
	 */
	virtual void chatroomDeleteOK(string roomId);

	/**
	 * 聊天室删除失败
	 */
	virtual void chatroomDeleteFailed(string roomId, string errString);

	/**
	 * 聊天室禁言成功
	 */
	virtual void chatroomBanToSendMsgOK(string banUserId, int banTime);

	/**
	 * 聊天室禁言失败
	 */
	virtual void chatroomBanToSendMsgFailed(string banUserId, int banTime, string errString);

	/**
	 * 聊天室踢人成功
	 */
	virtual void chatroomKickOutOK(string kickOutUserId);

	/**
	 * 聊天余额不足
	 */
	virtual void chatroomSendMsgNoFee();

	/**
	 * 聊天室踢人失败
	 */
	virtual void chatroomKickOutFailed(string kickOutUserId, string errString);

	/**
	 * 聊天室 自己被禁言
	 */
	virtual void chatroomSendMsgBanned(int remainTimeSec);

	/**
	 * 聊天室 自己被踢出
	 */
	virtual void chatroomKickedOut();

	/**
	 * 聊天室 收到消息
	 */
	virtual void chatroomGetNewMsg(CIMMessage* pMsg);

	/**
	 * 聊天室 收到私信消息
	 */
	virtual void chatroomGetNewPrivateMsg(CIMMessage* pMsg);

	/**
	 * 聊天室在线人数
	 */
	virtual void getRoomOnlineNumber(string roomId, int number);

	/**
	 * 聊天室在线人数
	 */
	virtual void sendMessageSuccess(int msgIndx);

	/**
	 * 聊天室在线人数
	 */
	virtual void sendMessageFailed(int msgIndx);

	/**
	 * 收到控制消息
	 */
	virtual void revControlMessage(string fromID, int code);

	/**
	 * 成功
	 * @param data
	 */
	virtual void success();

	/**
	 * 失败
	 * @param errMsg
	 */
	virtual void failed(string errMsg);

	string getChatroomId();
private:
	
	CUserManager* m_pUserManager;
	IChatroomManagerListener* m_pChatroomManagerListener;
	string m_strChatRoomServerIp;
	int m_nChatRoomServerPort;

	bool m_bJoinChatRoom;

	bool m_bReturn;
	bool m_bSuccess;
	string m_strErrInfo;

	string m_ChatRoomId;
};

