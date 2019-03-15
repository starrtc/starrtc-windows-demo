#pragma once
class CPicControlCallback
{
public:
	virtual void liveExit(void* pParam) = 0;
	virtual void changeStreamConfig(void* pParam, int upid) = 0;
	virtual void closeCurrentLive(void* pParam) = 0;
	virtual void startFaceFeature(void* pParam) = 0;
	virtual void stopFaceFeature(void* pParam) = 0;
};

