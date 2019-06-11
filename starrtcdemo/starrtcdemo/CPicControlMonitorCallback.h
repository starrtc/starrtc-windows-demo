#pragma once
#include <string>
using namespace std;
class CPicControlMonitorCallback
{
public:
	virtual void closeCurrentLive(void* pParam) = 0;
	virtual void startFaceFeature(void* pParam) = 0;
	virtual void stopFaceFeature(void* pParam) = 0;
};

