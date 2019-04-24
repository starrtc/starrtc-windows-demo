#pragma once
class ISoundCallback
{
public:
	virtual void getLocalSoundData(char* pData, int nLength) = 0;
	virtual void querySoundData(char** pData, int* nLength) = 0;
};