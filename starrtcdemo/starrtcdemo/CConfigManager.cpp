#pragma once
#include "stdafx.h"
#include "CConfigManager.h"
#include <string>
using namespace std;

CConfigManager::CConfigManager()
{
	readConfig();
}
CConfigManager::~CConfigManager()
{
}

bool CConfigManager::readConfig()
{
	//向D盘写入程序数据库连接ini文件信息，默认设置如下
	string strPath = ".\\param.ini";
	//CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用
	//BOOL ifFind = finder.FindFile(strPath);
	if (true)
	{

		char buf[256] = { 0 };
		::GetPrivateProfileString("param", "AEventCenterEnable", "", buf, sizeof(buf), strPath.c_str());
		int nAEventCenterEnable = atoi(buf);
		if (nAEventCenterEnable == 0)
		{
			m_bAEventCenterEnable = false;
		}
		else
		{
			m_bAEventCenterEnable = true;
		}
	}
	return true;
}
