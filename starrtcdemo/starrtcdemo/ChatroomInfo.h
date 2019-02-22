#pragma once
#include <string>
using namespace std;
class ChatroomInfo
{
public:
	ChatroomInfo() 
	{
		m_strName = "";
	}
	~ChatroomInfo() {}
public:
	string m_strName;
	string m_strCreaterId;
	string m_strRoomId;
};