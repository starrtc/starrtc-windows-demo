#pragma once
#include <string>
using namespace std;
#include "CPicControl.h"
class CRecvData
{
public:
	CRecvData()
	{
		m_pData = NULL;
		m_nDataLength = 0;
	}

	~CRecvData()
	{
		if (m_pData != NULL)
		{
			delete[] m_pData;
			m_pData = NULL;
		}

		m_nDataLength = 0;
	}

	void setData(uint8_t* pData, int nDataLength)
	{
		if (m_pData != NULL)
		{
			delete[] m_pData;
			m_pData = NULL;
		}
		m_pData = new uint8_t[nDataLength];
		memcpy(m_pData, pData, sizeof(uint8_t)*nDataLength);
		m_nDataLength = nDataLength;

	}

public:
	uint8_t* m_pData;
	int m_nDataLength;
};

class CUpUserInfo
{
public:
	CUpUserInfo()
	{
		m_pPictureControl = NULL;
		m_bUse = false;
		m_bBigPic = false;
		m_nTimes = 0;
	}
	~CUpUserInfo()
	{
		m_pPictureControl = NULL;
		m_bUse = false;
		m_bBigPic = false;
	}
public:
	int m_upid;
	CPicControl* m_pPictureControl;
	CRect m_showRect;
	bool m_bUse;
	bool m_bBigPic;
	int m_nTimes;
};

class CLiveUserInfo
{
public:
	CLiveUserInfo();
	~CLiveUserInfo();
};

