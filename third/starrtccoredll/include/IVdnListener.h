#pragma once
#include <stdint.h>

class IVdnListener
{
public:
	virtual int applyDownloadChannelOK() = 0;
	virtual int applyDownloadChannelFailed(char* errString) = 0;
	virtual int downloadChannelError(char* errString) = 0;
	virtual int downloadStopOK() = 0;
	virtual int downloadChannelClosed() = 0;
	virtual int downloadChannelLeave() = 0;
	virtual int downloadNetworkUnnormal() = 0;
	virtual int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum) = 0;
	virtual int uploaderAdd(char* upUserId, int upId) = 0;
	virtual int uploaderRemove(char* upUserId, int upId) = 0;
	virtual int downloadStreamConfigOK(char* channelId) = 0;
	virtual int downloadStreamConfigFailed() = 0;
	virtual int getRealtimeData(int upId, uint8_t* data, int len) = 0;
};