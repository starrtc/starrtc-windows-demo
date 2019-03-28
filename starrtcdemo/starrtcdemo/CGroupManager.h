#pragma once
#include "IGroupManagerListener.h"
#include "IGroupGetListListener.h"
#include "IGroupListener.h"
#include "CIMMessage.h"
#include "StarRtcCore.h"
#include <list>
#include <map>
using namespace std;

class CGroupManager : public IGroupListener
{
public:
	CGroupManager(CUserManager* pUserManager);
	~CGroupManager();
public:
	static void addGroupGetListListener(IGroupGetListListener* pGroupGetListListener);
	static void getGroupList(CUserManager* pUserManager);
	static void getUserList(CUserManager* pUserManager, string strGroupId);
	/**
	 * 添加监听
	 * @param groupManagerListener
	 */
	void addListener(IGroupManagerListener* pGroupManagerListener);

	/**
	 * 创建群
	 * @param groupName
	 * @param callback
	 */
	bool createGroup(string groupName);

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
	 * @param callback
	 * @return 发出的消息
	 */
	CIMMessage* sendMessage(string groupID, list<string> atUserIDs, string Message);

	/**
	 *发送消息
	 * @param groupID
	 * @param atUserIDs
	 * @param Message
	 * @param callback
	 * @return 发出的消息
	 */
	CIMMessage* sendOnlineMessage(string groupID, list<string> atUserIDs, string Message);
public:
	/**
	 * 获取group list回调函数
	 */
	virtual int applyGetGroupListFin(list<CGroupInfo>& groupInfoList);
	virtual int applyGetUserListFin(list<string>& userList);
	/**
	 * 群成员数发生变化
	 * @param groupID
	 * @param number
	 */
	virtual void onMembersUpdeted(string groupID, int number);

	/**
	 * 自己被移出群组
	 * @param groupID
	 */
	virtual void onSelfKicked(string groupID);

	/**
	 * 群组已经被删除
	 * @param groupID
	 */
	virtual void onGroupDeleted(string groupID);

	/**
	 *  收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(string groupId, CIMMessage* pMessage);

	/**
	 *  创建群组回调
	 * @param message
	 */
	virtual void onApplyCreateGroupFin(string groupID);

	/**
	 *  删除群组回调
	 * @param message
	 */
	virtual void onApplyDelGroupFin(string groupID);

	/**
	 *  添加成员回调
	 * @param message
	 */
	virtual void onApplyAddUserToGroupFin(string groupID);

	/**
	 *  删除成员回调
	 * @param message
	 */
	virtual void onApplyRemoveUserFromGroupFin(string groupID);
	
private:
	static IGroupGetListListener* m_pGroupGetListListener;
	IGroupManagerListener* m_pGroupManagerListener;
	StarRtcCore* m_pStarRtcCore;
	map<string, CIMMessage*> m_MsgMap;
};

