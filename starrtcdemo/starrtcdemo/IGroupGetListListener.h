#pragma once
#include <list>
#include "CGroupInfo.h"
class IGroupGetListListener
{
public:
	/**
	 * 查询群组列表回调
	 */
	virtual int applyGetGroupListFin(list<CGroupInfo>& groupInfoList) = 0;

	/**
	 * 查询用户列表回调
	 */
	virtual int applyGetUserListFin(list<string>& userList) = 0;
};
