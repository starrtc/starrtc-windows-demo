#pragma once
#include <string>
using namespace std;
class CPicControlCallback
{
public:
	virtual void changeShowStyle(string strUserId) = 0;
	virtual void closeCurrentLive() = 0;
};

