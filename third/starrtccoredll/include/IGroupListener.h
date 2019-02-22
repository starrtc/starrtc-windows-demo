#pragma once
#include "CIMMessage.h"
#include <string>
using namespace std;

class IGroupListener
{
public:
	IGroupListener() {}
	virtual ~IGroupListener() {}
public:
	/**
	 * 群成员数发生变化
	 * @param groupID
	 * @param number
	 */
	virtual void onMembersUpdeted(string groupID, int number) = 0;

	/**
	 * 自己被移出群组
	 * @param groupID
	 */
	virtual void onSelfKicked(string groupID) = 0;

	/**
	 * 群组已经被删除
	 * @param groupID
	 */
	virtual void onGroupDeleted(string groupID) = 0;

	/**
	 *  收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(string groupId, CIMMessage* pMessage) = 0;

	virtual void onApplyCreateGroupFin(string groupID) = 0;

	/**
	 *  删除群组回调
	 * @param message
	 */
	virtual void onApplyDelGroupFin(string groupID) = 0;

	/**
	 *  添加成员回调
	 * @param message
	 */
	virtual void onApplyAddUserToGroupFin(string groupID) = 0;

	/**
	 *  删除成员回调
	 * @param message
	 */
	virtual void onApplyRemoveUserFromGroupFin(string groupID) = 0;
};

