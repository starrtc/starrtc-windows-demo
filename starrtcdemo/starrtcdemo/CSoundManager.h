#pragma once
#include "PlaySound.h"
#include "RecodeSound.h"
class CSoundManager : public ISoundCallback
{
public:
	CSoundManager(ISoundCallback* pSoundCallback);
	virtual ~CSoundManager();
public:
	virtual void getLocalSoundData(char* pData, int nLength);
	virtual void querySoundData(char** pData, int* nLength);
	void startSoundData(bool bGetLocalData);
	void stopSoundData();

	void startGetSoundData();
	void stopGetSoundData();
	void setSoundData(char* pData, int nLength);
public:
	bool m_bExit;
	bool m_bStop;
	HANDLE m_hQueueSoundDataEvent;
	ISoundCallback* m_pSoundCallback;
private:
	CRecodeSound* m_pRecodeSound;
	CPlaySound* m_pPlaySound;
	
	HANDLE m_hQueueSoundDataThread;
	
	BOOL m_bGetSoundData;
	bool m_bGetLocalData;
};

