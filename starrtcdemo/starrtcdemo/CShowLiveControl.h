#pragma once
#include <vector>

#include "CPicControl.h"
#include "CLiveUserInfo.h"
#include "CUtil.h"
using namespace std;
#define UPID_MAX_SIZE 7

enum LIVE_SHOW_TYPE
{
	LIVE_SHOW_TYPE_VOIP,
	LIVE_SHOW_TYPE_LIVE
};

class CShowLiveControl
{
public:
	CShowLiveControl();
	~CShowLiveControl();
public:
	void setDrawRect(CRect drawRect);
	void setShowPictures();

	void setVoipShow();
	void setLiveShow();

	void resetPicControlPos();

	CUpUserInfo* findUpUserInfo(int upid);
	void addUpId(int nUpId);
	bool removeUpUser(int upid);
	bool removeAllUpUser();
	
	void drawPic(YUV_TYPE type, int upid, int w, int h, uint8_t* videoData, int videoDataLen);
	void drawPic(int upid, int w, int h, CImage image);
public:
	CPicControl* m_pPictureControlArr[UPID_MAX_SIZE];
	int m_configArr[UPID_MAX_SIZE];
	vector<CUpUserInfo*> m_upUserInfoArr;
	CRITICAL_SECTION m_critPicture;
	CRect m_DrawRect;
	LIVE_SHOW_TYPE m_showType;
};

