#pragma once
#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif

#include "CChatroomManager.h"
#include "IChatroomManagerListener.h"

/*
 *聊天室管理类
 */
class MATH_API XHChatroomManager
{
public:
	/*
	 * 构造函数
	 * @param pUserManager 用户信息
	 * @param pChatroomManagerListener 回调函数指针
	 */
	XHChatroomManager(IChatroomManagerListener* pChatroomManagerListener);
	/*
	 * 析构函数
	 */
	~XHChatroomManager();
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
	static void getChatroomList(int listType);

	/*
	 * 创建ChatRoom
	 * @param strName 名字
	 * @param chatroomType 类型
	 */
	bool createChatRoom(string strName, int chatroomType);

	/**
	 * 删除聊天室
	 * @param strChatroomId 删除的聊天室ID
	 */
	bool deleteChatRoom(string strChatroomId);

	/**
	 * 加入聊天室
	 * @param strChatroomId 要加入的聊天室ID
	 */
	bool joinChatRoom(string strChatroomId);

	/**
	 * 退出聊天室
	 * @param strChatroomId 要退出的聊天室ID
	 */
	bool exitChatroom(string strChatroomId);

	/**
	 * 禁言聊天室内的用户
	 * @param strChatroomId 所在聊天室ID
	 * @param strMemberId 被禁言的用户ID
	 * @param muteSeconds 禁言时长（单位：秒）
	 */
	bool muteMember(string strChatroomId, string strMemberId, int muteSeconds);

	/**
	 * 解除用户的禁言
	 * @param chatroomID 所在聊天室ID
	 * @param memberID 解除禁言的用户ID
	 */
	bool unMuteMember(string strChatroomId, string strMemberId);

	/**
	 * 从聊天室踢出用户
	 * @param chatroomID 所在聊天室ID
	 * @param memberID 踢出的用户ID
	 */
	bool kickMember(string chatroomID, string memberID);

	/*
	 * 发送消息
	 * @param strMsg 消息内容
	 */
	CIMMessage* sendMessage(string strMsg);

	/*
	 * 发送私信
	 * @param toUserId 对方userId
	 * @param msgData 消息内容
	 */
	CIMMessage* sendPrivateChat(string toUserId, char* msgData);

	/**
	 * 查询列表
	 * @param userId 用户Id
	 * @param callback 结果回调
	 */
	void queryList(string userId, string type);

	/**
	 * 从列表删除
	 * @param userId 用户Id
	 * @param chatroomId 聊天室ID
	 */
	void deleteFromList(string userId, int type, string chatroomId);
	/*
	 * 查询chatroom在线人数
	 */
	bool getOnlineNumber(string strChatroomId);

	/**
	 * 获取当前Chatroom id
	 * @return Chatroom id
	 */
	string getChatroomId();
private:
	CChatroomManager* m_pChatroomManager;
};

