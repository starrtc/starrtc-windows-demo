#pragma once
#include "CIMMessage.h"
#include <string>
using namespace std;

class CMsgUtil
{
public:
	static string toJson(CIMMessage* msg);
	static void getJson(CIMMessage* msg, char* strData);
	
};

