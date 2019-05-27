#pragma once
#include "CIMMessage.h"
#include <string>
#include "CGroupInfo.h"
using namespace std;

class IGroupManagerListener
{
public:
	IGroupManagerListener() {}
	virtual ~IGroupManagerListener() {}
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
};

