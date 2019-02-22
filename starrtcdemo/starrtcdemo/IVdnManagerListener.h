#pragma once
#include <stdint.h>
#include "ILiveManagerListener.h"
class IVdnManagerListener : public ILiveManagerListener
{
public:
	virtual int downloadChannelClosed() = 0;
	virtual int downloadChannelLeave() = 0;
	virtual int downloadNetworkUnnormal() = 0;
	virtual int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum) = 0;
};