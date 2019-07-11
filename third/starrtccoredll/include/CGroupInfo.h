#pragma once
#include <string>
#include <list>
using namespace std;
class CGroupInfo
{
public:
	string m_strName;
	string m_strCreaterId;
	string m_strId;
};

class CGroupMemoryInfo
{
public:
	list<string> m_UserIdList;
	bool m_bIgnore;
};
