// PlaySound.cpp : 实现文件
//

#include "stdafx.h"
//#include "VideoPlay.h"
#include "PlaySound.h"


// CPlaySound

IMPLEMENT_DYNCREATE(CPlaySound, CWinThread)

CPlaySound::CPlaySound()
{
	//初始化音频格式结构体
	memset(&m_WaveFormatEx, 0, sizeof(m_WaveFormatEx));
	m_WaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormatEx.nChannels = 1;
	m_WaveFormatEx.wBitsPerSample = 16;
	m_WaveFormatEx.cbSize = 0;
	m_WaveFormatEx.nSamplesPerSec = 16000;
	m_WaveFormatEx.nBlockAlign = 2;
	m_WaveFormatEx.nAvgBytesPerSec = 32000;
	m_IsPlaying = FALSE;	
}

CPlaySound::~CPlaySound()
{

}

BOOL CPlaySound::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int CPlaySound::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

void CPlaySound::OnStartPlaying(WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmReturn = 0;

	if(m_IsPlaying) //已经开始播放则直接返回
		return; //FALSE;
	//打开音频输出设备
	mmReturn = ::waveOutOpen( &m_hPlay, WAVE_MAPPER,
		&m_WaveFormatEx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);

	if(mmReturn) //打开设备失败
		displayError(mmReturn,"PlayStart");	
	else
	{	
		m_IsPlaying = TRUE;
		DWORD volume = 0xffffffff;
		waveOutSetVolume(m_hPlay, volume);//设置输出设备的输出量
	}			
}

void CPlaySound::displayError(int code,char mesg[])
{
	TCHAR errorbuffer[MAX_PATH];
	TCHAR errorbuffer1[MAX_PATH];

	waveOutGetErrorText( code,errorbuffer,MAX_PATH);
	wsprintf(errorbuffer1, TEXT("PLAY : %s :%x:%s") ,mesg,code,errorbuffer);
	AfxMessageBox(errorbuffer1);  
}

void CPlaySound::OnStopPlaying(WPARAM wParam, LPARAM lParam)
{

	MMRESULT mmReturn = 0;

	if(m_IsPlaying == FALSE)
		return;// FALSE;

	mmReturn = ::waveOutReset(m_hPlay);//重置输出设备，重置能够使输出设备全部buffer输出结束

	if(!mmReturn)
	{
		m_IsPlaying = FALSE;
		Sleep(500); //等待所有buffer输出完成
		mmReturn = ::waveOutClose(m_hPlay);//关闭设备
	}
}

void CPlaySound::OnEndPlaySoundData(WPARAM wParam, LPARAM lParam)
{
	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;

	if(lpHdr)
	{
		::waveOutUnprepareHeader(m_hPlay, lpHdr, sizeof(WAVEHDR));//音频输出结束，清空buffer
	}
	return ;//ERROR_SUCCESS;
}

void CPlaySound::OnWriteSoundData(WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmResult = 0;
	int length=(int) wParam;
	char* pData = (char *)lParam;
	if (m_IsPlaying == FALSE)
	{
		return; //FALSE;
	}
		
	// Prepare wave header for playing 
	WAVEHDR *lpHdr=new WAVEHDR;
	memset(lpHdr,0,sizeof(WAVEHDR));
	lpHdr->lpData= pData;
	lpHdr->dwBufferLength=length;

	//将要输出的数据写入buffer
	mmResult = ::waveOutPrepareHeader(m_hPlay, lpHdr, sizeof(WAVEHDR));

	if(mmResult)
	{
		return ;//ERROR_SUCCESS;
	}

	//将输出数据发送给输出设备
	mmResult = ::waveOutWrite(m_hPlay, lpHdr, sizeof(WAVEHDR));
	if(mmResult)
	{
		return ;//ERROR_SUCCESS;				
	}
	return ;//ERROR_SUCCESS;
}

void CPlaySound::OnEndThread(WPARAM wParam, LPARAM lParam)
{
	// If already playing then stop it...
	if(m_IsPlaying)
		OnStopPlaying(0, 0);
	// Quit this thread...
	::PostQuitMessage(0);

	return ;//TRUE;
}

BEGIN_MESSAGE_MAP(CPlaySound, CWinThread)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_STARTPLAYING, OnStartPlaying)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_STOPPLAYING, OnStopPlaying)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_PLAYBLOCK, OnWriteSoundData)
	ON_THREAD_MESSAGE(MM_WOM_DONE, OnEndPlaySoundData)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_ENDTHREAD,OnEndThread)
END_MESSAGE_MAP()


// CPlaySound 消息处理程序
