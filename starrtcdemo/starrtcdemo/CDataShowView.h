#pragma once
#include <vector>

#include "CPicControl.h"
#include "CLiveUserInfo.h"
#include "CUtil.h"
using namespace std;
#define UPID_MAX_SIZE 8

#define UPDATE_SHOW_PIC_MESSAGE WM_USER+1000
class CDataShowView
{
public:
	CDataShowView();
	~CDataShowView();

	void setDrawRect(CRect drawRect);
	void setShowPictures();

	void addUpId(int nUpId);
	CUpUserInfo* findUpUserInfo(int upid);

	bool removeAllUpUser();
	bool removeUpUser(int upid);
	void drawPic(YUV_TYPE type, int upid, int w, int h, uint8_t* videoData, int videoDataLen);
	void drawPic(int upid, int w, int h, CImage image);
public:
	CPicControl* m_pPictureControlArr[UPID_MAX_SIZE];
	int m_configArr[UPID_MAX_SIZE];
	vector<CUpUserInfo*> m_upUserInfoArr;
	CRITICAL_SECTION m_critPicture;
	CRect m_DrawRect;
};

