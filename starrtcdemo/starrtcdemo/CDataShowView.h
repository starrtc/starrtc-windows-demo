#pragma once
#include <vector>

#include "CPicControl.h"
#include "CLiveUserInfo.h"
#include "CUtil.h"
using namespace std;
#define UPID_MAX_SIZE 7

#define UPDATE_SHOW_PIC_MESSAGE WM_USER+1000
class CDataShowView
{
public:
	CDataShowView();
	virtual ~CDataShowView();

	CUpUserInfo* findUpUserInfo(string strUserId);
	bool addUser(string strUserId, bool isBigPic);
	bool removeUser(string strUserId);
	void removeAllUser();
	bool isLeftOneUser(string& strUserId);
	int getUserCount();
	string changeShowStyle(string strUserId, bool bBigPic);
	void setDrawRect(CRect drawRect);
	void setShowPictures();
	void drawPic(YUV_TYPE type, string userId, int w, int h, uint8_t* videoData, int videoDataLen);
	void drawPic(string userId, int w, int h, CImage image);
public:
	vector<CPicControl*> m_pPictureControlArr;
	vector<CUpUserInfo*> m_upUserInfoArr;
	CRITICAL_SECTION m_critPicture;
	CRect m_DrawRect;
};

