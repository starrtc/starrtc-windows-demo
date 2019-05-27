#pragma once
#include "IChatroomManagerListener.h"
#include "IStarIMChatroomListener.h"
#include "IChatroomGetListListener.h"
#include "CUserManager.h"
#include <list>
#include "ChatroomInfo.h"
#include <string>
using namespace std;

enum CHATROOM_TYPE
{
	CHATROOM_TYPE_UNABLE,	// 占位
	CHATROOM_TYPE_PUBLIC,	// 无需登录和验证
	CHATROOM_TYPE_LOGIN		// 需要登录，无需验证
};

enum CHATROOM_LIST_TYPE
{
	CHATROOM_LIST_TYPE_CHATROOM,	
	CHATROOM_LIST_TYPE_LIVE,	
	CHATROOM_LIST_TYPE_LIVE_PUSH,
	CHATROOM_LIST_TYPE_MEETING,
	CHATROOM_LIST_TYPE_MEETING_PUSH,
	CHATROOM_LIST_TYPE_CLASS,
	CHATROOM_LIST_TYPE_CLASS_PUSH
};

/*
 *聊天室管理类
 */
class CChatroomManager : public IStarIMChatroomListener
{
public:
	/*
	 * 构造函数
	 * @param pUserManager 用户信息
	 * @param pChatroomManagerListener 回调函数指针
	 */
	CChatroomManager(CUserManager* pUserManager, IChatroomManagerListener* pChatroomManagerListener);
	/*
	 * 析构函数
	 */
	~CChatroomManager();
public:
	/*
	 * 添加获取列表后回调函数指针
	 * @param pChatroomGetListListener 回调函数指针
	 */
	static void addChatroomGetListListener(IChatroomGetListListener* pChatroomGetListListener);
	
	/*
	 * 获取聊天室列表
	 * @param pUserManager 用户信息
	 * @param listType 类型
	 */
	static void getChatroomList(CUserManager* pUserManager, int listType);

	/*
	 * 重置返回值
	 */
	void resetReturnVal();

	/*
	 * 设置chatroom id
	 * @param chatRoomId chatroom id
	 */
	void setChatroomId(string chatRoomId);

	/*
	 * 通过调度获取ChatRoom服务地址
	 */
	bool getChatRoomServerAddr();

	/*
	 * 创建ChatRoom
	 * @param strName 名字
	 * @param chatroomType 类型
	 */
	bool createChatRoom(string strName, int chatroomType);

	/*
	 * 加入ChatRoom
	 */
	bool joinChatRoom(string strChatroomId);
	/*
	 * 查询chatroom在线人数
	 */
	bool getOnlineNumber(string strChatroomId);

	bool banToSendMsg(char* banUserId, int banTime);
	bool kickOutUser(char* kickOutUserId);

	/*
	 * 发送消息
	 * @param pIMMessage 消息内容
	 */
	bool sendChat(CIMMessage* pIMMessage);

	/*
	 * 发送私信
	 * @param toUserId 对方userId
	 * @param msgData 消息内容
	 */
	bool sendPrivateChat(string toUserId, char* msgData);

	/*
	 * 发送控制消息
	 * @param targetId 对方targetId
	 * @param code 消息类型
	 */
	bool sendChatroomPrivateControlMessage(string targetId, int code);

	/*
	 * 删除聊天室
	 */
	bool deleteChatRoom();

	/*
	 * 创建后上报创建的聊天室信息
	 */
	bool reportChatroom(string strRoomId, ChatroomInfo& chatroomInfo, int listType);

	/**
	 * 退出聊天室
	 * @param strChatroomId 要退出的聊天室ID
	 */
	bool exitChatroom(string strChatroomId);

	/*
	 *  退出
	 */
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
	 * 查询聊天室列表回调
	 */
	virtual int chatroomQueryAllListOK(list<ChatroomInfo>& chatRoomInfoList);

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

	/**
	 * 获取当前Chatroom id
	 * @return Chatroom id
	 */
	string getChatroomId();
private:
	//用户信息
	CUserManager* m_pUserManager;
	//回调函数指针
	IChatroomManagerListener* m_pChatroomManagerListener;
	//获取列表回调函数指针
	static IChatroomGetListListener* m_pChatroomGetListListener;
	//服务器Ip
	string m_strChatRoomServerIp;
	//服务器端口号
	int m_nChatRoomServerPort;
	bool m_bJoinChatRoom;
	bool m_bReturn;
	bool m_bSuccess;
	string m_strErrInfo;
	string m_ChatRoomId;
};

