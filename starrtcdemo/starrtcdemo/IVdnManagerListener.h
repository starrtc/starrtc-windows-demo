#pragma once
#include <stdint.h>
class IVdnManagerListener
{
public:
	virtual int uploaderAddVdn(char* upUserId, int upId) = 0;
	virtual int uploaderRemoveVdn(char* upUserId, int upId) = 0;
	virtual int getRealtimeDataVdn(int upId, uint8_t* data, int len) = 0;
	virtual int getVideoRawVdn(int upId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;

	virtual int downloadChannelClosed() = 0;
	virtual int downloadChannelLeave() = 0;
	virtual int downloadNetworkUnnormal() = 0;
	virtual int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum) = 0;
};