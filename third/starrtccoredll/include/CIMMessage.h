#pragma once
#include <string>
using namespace std;

class CIMMessage
{
public:	
	long long m_Time;               //消息时间
	int m_nMsgIndex;            //消息编号
	
	int m_nType;                //消息类型：  0：SDK内部消息，1：用户消息
	int m_nCode;                //消息类型=0 时的业务码

	string m_strFromId;           //发送消息的人
	string m_strTargetId;         //目标id（可是个人或群组id）
	string m_strContentData;      //自定义消息内容
	string m_strAtList;           // @的用户ID 多个用逗号分隔
};

