#include "stdafx.h"
#include "CSoundManager.h"
#include <stdint.h>
DWORD WINAPI QuerySoundDataThread(LPVOID p)
{
	CSoundManager* pSoundManager = (CSoundManager*)p;

	while (WaitForSingleObject(pSoundManager->m_hQueueSoundDataEvent, INFINITE) == WAIT_OBJECT_0)
	{
		if (pSoundManager->m_bExit)
		{
			break;
		}
		while (pSoundManager->m_bExit == false && pSoundManager->m_bStop == false)
		{
			if (pSoundManager->m_pSoundCallback != NULL)
			{
				uint8_t* pData = NULL;
				int nLength = 0;
				pSoundManager->m_pSoundCallback->querySoundData((char**)&pData, &nLength);
				if (pData != NULL && nLength > 0)
				{
					if (pData[0] == 0 && pData[1] == 0 && pData[2] == 0 && pData[3] == 0 &&
						pData[nLength - 1] == 0 && pData[nLength - 2] == 0 && pData[nLength - 3] == 0 && pData[nLength - 4] == 0)
					{
						delete pData;
						pData = NULL;
						Sleep(16);
					}
					else
					{
						pSoundManager->setSoundData((char*)pData, nLength);
					}
				}
				else
				{
					Sleep(16);
				}
			}
		}
	}
	return 0;
}

CSoundManager::CSoundManager(ISoundCallback* pSoundCallback)
{
	m_pSoundCallback = pSoundCallback;
	m_bExit = false;
	m_bGetLocalData = true;
	m_pPlaySound = new CPlaySound;
	m_pPlaySound->CreateThread();
	m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_STARTPLAYING, 0, 0);

	m_pRecodeSound = new CRecodeSound(NULL);
	m_pRecodeSound->setCallback(this);
	m_pRecodeSound->CreateThread();
	//m_pRecodeSound->PostThreadMessage(WM_RECORDSOUND_STARTRECORDING, 0, 0);
	m_bGetSoundData = FALSE;
	m_hQueueSoundDataEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hQueueSoundDataThread = CreateThread(NULL, 0, QuerySoundDataThread, (void*)this, 0, 0); // 创建线程
}


CSoundManager::~CSoundManager()
{
	m_bStop = true;
	m_bExit = true;
	m_bGetLocalData = false;
	if (m_hQueueSoundDataEvent != NULL)
	{
		SetEvent(m_hQueueSoundDataEvent);
		CloseHandle(m_hQueueSoundDataEvent);
		m_hQueueSoundDataEvent = NULL;
	}
	m_pSoundCallback = NULL;

	if (m_pPlaySound != NULL)
	{
		m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_STOPPLAYING, 0, 0);
		m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_ENDTHREAD, 0, 0);
	}

	if (m_pRecodeSound != NULL)
	{
		m_pRecodeSound->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING, 0, 0);
		m_pRecodeSound->PostThreadMessage(WM_RECORDSOUND_ENDTHREAD, 0, 0);
	}
}

void CSoundManager::getLocalSoundData(char* pData, int nLength)
{
	if (m_pSoundCallback != NULL && pData != NULL)
	{
		m_pSoundCallback->getLocalSoundData(pData, nLength);
	}
}

void CSoundManager::querySoundData(char** pData, int* nLength)
{

}

void CSoundManager::startGetSoundData(bool bGetLocalData)
{
	if (bGetLocalData)
	{
		if (m_pRecodeSound != NULL)
		{
			m_pRecodeSound->PostThreadMessage(WM_RECORDSOUND_STARTRECORDING, 0, 0);
		}
		m_bGetLocalData = bGetLocalData;
	}
	
	if (m_pPlaySound != NULL)
	{
		m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_STARTPLAYING, 0, 0);
	}

	m_bGetSoundData = TRUE;
	m_bStop = false;
	SetEvent(m_hQueueSoundDataEvent);
	
	
}
void CSoundManager::stopGetSoundData()
{
	m_bStop = true;
	if (m_bGetLocalData)
	{
		if (m_pRecodeSound != NULL)
		{
			m_pRecodeSound->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING, 0, 0);
		}
		m_bGetLocalData = false;
	}
	m_bGetSoundData = FALSE;
	if (m_pPlaySound != NULL)
	{
		m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_STOPPLAYING, 0, 0);
	}
}

void CSoundManager::setSoundData(char* pData, int nLength)
{
	if (m_pPlaySound != NULL /*&& m_bGetSoundData*/)
	{
		m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_PLAYBLOCK, nLength, (LPARAM)pData);
	}
}
