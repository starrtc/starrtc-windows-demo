#pragma once
#include "CUserManager.h"
#include <stdint.h>
class CCodecManager
{
public:
	CCodecManager(CUserManager* pUserManager);
	virtual ~CCodecManager();
public:
	void insertAudioRaw(uint8_t* audioData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	//裁剪视频并生成小图,outVideoDataBig与outVideoDataSmall在函数内malloc,由ios自己free，若无小图，则outVideoDataSmall指向的为NULL
	//videoData由在函数内释放
	//成功返回0，失败返回-1
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	void querySoundData(uint8_t** pData, int* nLength);
public:
	CUserManager* m_pUserManager;
};

