#pragma once
#include <stdint.h>
class  IRecvDataListener
{
public:

	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;
};
