#pragma once

#include<mmsystem.h>
#include<mmreg.h>
#pragma  comment(lib, "winmm.lib")

#define WM_PLAYSOUND_STARTPLAYING	WM_USER+600
#define WM_PLAYSOUND_STOPPLAYING	WM_USER+601
#define WM_PLAYSOUND_PLAYBLOCK		WM_USER+602
#define WM_PLAYSOUND_ENDTHREAD		WM_USER+603

#define SOUNDSAMPLES 1000
#define PLAYBUFFER   600
#define SAMPLEPSEC   8000

// CPlaySound
class CPlaySound : public CWinThread
{
	DECLARE_DYNCREATE(CPlaySound)
public:
	CPlaySound();
	~CPlaySound();
	virtual BOOL InitInstance();
	virtual int ExitInstance();
private:
	void displayError(int code,char mesg[]);
	WAVEFORMATEX		m_WaveFormatEx;
	BOOL				m_IsPlaying;
	HWAVEOUT			m_hPlay;
protected:
	afx_msg void OnStartPlaying(WPARAM wParam, LPARAM lParam);
	afx_msg void OnStopPlaying(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEndPlaySoundData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnWriteSoundData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEndThread(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


