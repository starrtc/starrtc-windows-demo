#pragma once
#include <list>
#include "ChatroomInfo.h"
class IChatroomGetListListener
{
public:
	/**
	 * 查询聊天室列表回调
	 */
	virtual int chatroomQueryAllListOK(list<ChatroomInfo>& listData) = 0;
};

