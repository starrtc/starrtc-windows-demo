#include "stdafx.h"
#include "ILiveInterface.h"


ILiveInterface::ILiveInterface(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
}


ILiveInterface::~ILiveInterface()
{
}
void ILiveInterface::setChannelId(string strChannelId)
{
	m_ChannelId = strChannelId;
}

void ILiveInterface::resetReturnVal()
{
	m_bReturn = false;
	m_bSuccess = false;
	m_strErrInfo = "";
}


/**
 * ³É¹¦
 * @param data
 */
void ILiveInterface::success()
{
	m_bSuccess = true;
	m_bReturn = true;
}

/**
 * Ê§°Ü
 * @param errMsg
 */
void ILiveInterface::failed(string errMsg)
{
	m_bSuccess = false;
	m_strErrInfo = errMsg;
	m_bReturn = true;
}

string ILiveInterface::getChannelId()
{
	return m_ChannelId;
}

