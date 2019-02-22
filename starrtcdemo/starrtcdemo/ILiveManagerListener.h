#pragma once
#include <stdint.h>
class ILiveManagerListener
{
public:
	virtual int uploaderAdd(char* upUserId, int upId) = 0;
	virtual int uploaderRemove(char* upUserId, int upId) = 0;
	virtual int getRealtimeData(int upId, uint8_t* data, int len) = 0;
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;
};