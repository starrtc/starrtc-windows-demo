#pragma once
#include <string>
using namespace std;
#define UPID_MAX_SIZE 8
#include <queue>
#include "CPicControl.h"
#include "CLiveUserInfo.h"
//#include "CFindFace.h"
enum SEND_MESSAGE_TYPE
{
	CHILD_PROCESS_ERROR,
	CHILD_PROCESS_INIT_SUCCESS,
	CHILD_PROCESS_LOGIN_FAILED,
	CHILD_PROCESS_JOIN_CHATROOM_FAILED,
	CHILD_PROCESS_APPLAY_DOWNLOAD_FAILED,
	CHILD_PROCESS_STOP_CHATROOM_FAILED,
	CHILD_PROCESS_STOP_APPLAY_DOWNLOAD_FAILED,
	CHILD_PROCESS_START_LIVE_SUCCESS,
	CHILD_PROCESS_RECV_VIDEO_DATA,
	CHILD_PROCESS_FACE_FEATURE,
	CHILD_PROCESS_FACE_FEATURE_INIT_FAILED,
	CHILD_PROCESS_ADD_UPID,
	CHILD_PROCESS_REMOVE_UPID,
	CHILD_PROCESS_CHANNEL_CLOSE,
	CHILD_PROCESS_CHANNEL_LEAVE,
	CHILD_PROCESS_REQUEST_LEAVE_SUCCESS,

	PARENT_PROCESS_START_LIVE,
	PARENT_PROCESS_SET_STREAM_CONFIG,
	PARENT_PROCESS_FACE_FEATURE,
	PARENT_PROCESS_LIVE_EXIT
};



class CProcessInfo
{
public:
	CProcessInfo(CWnd* pParentWnd, CRect drawRect);
	~CProcessInfo();
public:
	void drawPic(int upid, int w, int h, uint8_t* videoData, int videoDataLen);
	void drawBackground(CStatic* pPicture);
	bool setData(uint8_t* pData, int nDataLength);
	CUpUserInfo* findUpUserInfo(int upid);

	bool removeAllUpUser();
	bool removeUpUser(int upid);
	void clearUpUser();
	void setShowPictures();
	bool sendMessage(CString winName, CString strData);
	void setStreamConfig();

	void liveExit();

public:
	string m_strWindowName;
	bool m_bUse;
	bool m_bInit;
	vector<CUpUserInfo*> m_upUserInfoArr;
	CPicControl* m_pPictureControl;
	CPicControl* m_pPictureControlArr[UPID_MAX_SIZE];
	int m_configArr[UPID_MAX_SIZE];
	PROCESS_INFORMATION* m_pPi;
	string m_strChatRoomId;
	string m_strChannelId;
	CWnd* m_pParentWnd;
	CRect m_DrawRect;
	queue<CRecvData*> m_recvDataQueue;
	CRITICAL_SECTION m_crit;

	CRITICAL_SECTION m_critPicture;


	HANDLE m_hThread;
	bool m_bExit;
	bool m_bThreadExit;

	//	vector<CFindFaceResult> m_vFindFaceResult;
	CRITICAL_SECTION m_critFaceFeature;

};

