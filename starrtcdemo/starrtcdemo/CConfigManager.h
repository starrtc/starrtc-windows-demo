#pragma once

class CConfigManager
{
public:
	CConfigManager();
	~CConfigManager();
	bool readConfig();
public:
	bool m_bAEventCenterEnable;
	
};

