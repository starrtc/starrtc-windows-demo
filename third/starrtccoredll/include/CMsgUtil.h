#pragma once
#include "CIMMessage.h"
#include <string>
using namespace std;

class CMsgUtil
{
public:
	static string toJson(CIMMessage* msg);
	static void getJson(CIMMessage* msg, char* strData);

	static string UTF8toANSI(string strUTF8);
	static string ANSItoUTF8(string strAnsi);
	static wstring ANSIToUnicode(const string& str);
	static string UnicodeToANSI(const wchar_t* str);
	static unsigned char ToHex(unsigned char x);
	static unsigned char FromHex(unsigned char x);
	static std::string UrlEncode(const std::string& str);
	static std::string UrlDecode(const std::string& str);
};

