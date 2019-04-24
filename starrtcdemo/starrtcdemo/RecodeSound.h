#pragma once
#include "ISoundCallback.h"
#define WM_RECORDSOUND_STARTRECORDING	WM_USER+500
#define WM_RECORDSOUND_STOPRECORDING	WM_USER+501
#define WM_RECORDSOUND_ENDTHREAD		WM_USER+502

#define SAMPLERSEC 8000
#define MAXRECBUFFER 12
#define RECBUFFER  600		

#include<mmsystem.h>
#include<mmreg.h>
#pragma  comment(lib, "winmm.lib")

// CRecodeSound
class CRecodeSound : public CWinThread
{
	DECLARE_DYNCREATE(CRecodeSound)

public:
	CRecodeSound(CDialog *pDlg = NULL);                            // 动态创建所使用的受保护的构造函数
	virtual ~CRecodeSound();
	void setCallback(ISoundCallback* pCallback);
	virtual BOOL InitInstance();
	virtual int ExitInstance();

private:
	void PreCreateHeader();
	LPWAVEHDR CreateWaveHeader();
	void displayError(int mmReturn,char errmsg[]);

	ISoundCallback* m_pCallback;
	HWAVEIN			m_hRecord;		//音频输入设备
	WAVEFORMATEX	m_WaveFormatEx; //音频格式
	LPWAVEHDR		m_RecHead[MAXRECBUFFER];
	BOOL			m_IsRecoding;	//标识当前是否在录制音频
	int				m_IsAllocated;	//标识当前是否已经分配buffer
protected:
	afx_msg void OnStartRecording(WPARAM wParam, LPARAM lParam);
	afx_msg void OnStopRecording(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEndThread(WPARAM wParam, LPARAM lParam);
	void OnSoundData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};