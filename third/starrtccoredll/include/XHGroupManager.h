#pragma once
#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif

#include "IGroupManagerListener.h"
#include "IGroupGetListListener.h"
#include "CGroupManager.h"
class MATH_API XHGroupManager
{
public:
	/*
	 * 构造函数
	 * @param pUserManager 用户信息
	 */
	XHGroupManager(IGroupManagerListener* pGroupManagerListener);
	/*
	 * 析构函数
	 */
	~XHGroupManager();
public:
	/*
	 * 添加获取列表后回调函数指针
	 * @param pChatroomGetListListener 回调函数指针
	 */
	static void addGroupGetListListener(IGroupGetListListener* pGroupGetListListener);
	/*
	 * 获取群组列表
	 * @param pUserManager 用户信息
	 */
	static void getGroupList();
	/*
	 * 获取群组成员列表
	 * @param pUserManager 用户信息
	 * @param strGroupId 群组id
	 */
	static void getUserList(string strGroupId);

	/**
	 * 创建群
	 * @param groupName
	 */
	string createGroup(string groupName);

	/**
	 * 删除群
	 * @param groupID
	 */
	bool deleteGroup(string groupID);

	/**
	 * 添加群成员
	 * @param groupID
	 * @param memberIDs
	 */
	void addGroupMembers(string groupID, list<string> memberIDs);

	/**
	 * 删除群成员
	 * @param groupID
	 * @param memberIDs
	 */
	void deleteGroupMembers(string groupID, list<string> memberIDs);

	/**
	 * 设置推送开关
	 * @param groupID
	 * @param enable
	 * @param callback
	 */
	void setPushEnable(string groupID, bool enable);

	/**
	 *发送消息
	 * @param groupID
	 * @param atUserIDs
	 * @param Message
	 * @return 发出的消息
	 */
	CIMMessage* sendMessage(string groupID, list<string> atUserIDs, string Message);

	/**
	 *发送消息
	 * @param groupID
	 * @param atUserIDs
	 * @param Message
	 * @return 发出的消息
	 */
	CIMMessage* sendOnlineMessage(string groupID, list<string> atUserIDs, string Message);
private:
	CGroupManager* m_pGroupManager;
};

