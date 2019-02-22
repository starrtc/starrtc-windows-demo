#pragma once
class CPicControlCallback
{
public:
	CPicControlCallback();
	~CPicControlCallback();
public:
	virtual void liveExit(void* pParam);
	virtual void changeStreamConfig(void* pParam, int upid);
	virtual void closeCurrentLive(void* pParam);
	virtual void startFaceFeature(void* pParam);
	virtual void stopFaceFeature(void* pParam);
};

