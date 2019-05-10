#include "stdafx.h"
#include "CCodecManager.h"
#include "StarRtcCore.h"

CCodecManager::CCodecManager(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
}


CCodecManager::~CCodecManager()
{
}
void CCodecManager::insertAudioRaw(uint8_t* audioData, int dataLen)
{
	StarRtcCore::getStarRtcCoreInstance()->insertAudioRaw(audioData, dataLen);
}
//videoData的释放由此函数负责
void CCodecManager::insertVideoNalu(uint8_t* videoData, int dataLen)
{
	StarRtcCore::getStarRtcCoreInstance()->insertVideoNalu(videoData, dataLen);
}

//videoData的释放由此函数负责
void CCodecManager::insertVideoRaw(uint8_t* videoData, int dataLen, int isBig)
{
	StarRtcCore::getStarRtcCoreInstance()->insertVideoRaw(videoData, dataLen, isBig);
}

int CCodecManager::cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall)
{
	return StarRtcCore::getStarRtcCoreInstance()->cropVideoRawNV12(w, h, videoData, dataLen, yuvProcessPlan, rotation, needMirror, outVideoDataBig, outVideoDataSmall);
}

void CCodecManager::querySoundData(uint8_t** pData, int* nLength)
{
	StarRtcCore::getStarRtcCoreInstance()->querySoundData(pData, nLength);
}
