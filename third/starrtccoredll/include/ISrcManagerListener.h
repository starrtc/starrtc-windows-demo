#pragma once
#include <stdint.h>

class ISrcManagerListener
{
public:
	virtual int uploaderAddSrc(char* upUserId, int upId) = 0;
	virtual int uploaderRemoveSrc(char* upUserId, int upId) = 0;
	virtual int getRealtimeDataSrc(int upId, uint8_t* data, int len) = 0;
	virtual int getVideoRawSrc(int upId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;

	virtual int deleteChannel(char* channelId) = 0;
	virtual int stopOK() = 0;
	virtual int srcError(char* errString) = 0;
};
