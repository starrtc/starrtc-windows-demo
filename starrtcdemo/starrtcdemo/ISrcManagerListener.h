#pragma once
#include "ILiveManagerListener.h"
#include <stdint.h>
class ISrcManagerListener : public ILiveManagerListener
{
public:
	virtual int deleteChannel(char* channelId) = 0;
	virtual int stopOK() = 0;
	virtual int srcError(char* errString) = 0;
};
