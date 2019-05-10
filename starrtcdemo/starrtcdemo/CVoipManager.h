#pragma once
#include "IStarVoipListener.h"
#include "IVoipManagerListener.h"
#include "IRecvDataListener.h"
#include "IResultCallback.h"
#include "CCodecManager.h"
#include "CChatManager.h"

class CVoipManager : public IStarVoipListener, public IRecvDataListener, public IStarIMC2CListener
{
public:
	CVoipManager(CUserManager* pUserManager, IVoipManagerListener* pVoipManagerListener);
	virtual ~CVoipManager();
public:
	int init();
	void stopVoip(int isActive);
	/**
	 * 主叫方调用
	 * 发起通话
	 * @param toID
	 * @param callback
	 */
	bool call(string strTargetId);

	/**
	* 主叫方调用
	* 对方接听或拒绝前 主叫方主动取消呼叫
	*/
	void cancel();

	/**
	 * 被叫方调用
	 * 同意跟主叫方通话
	 * @param fromID
	 */
	void accept(string fromID);

	/**
	 * 被叫方调用
	 * 拒绝跟主叫方通话
	 */
	void refuse();

	/**
	 * 双方都可调用
	 * 挂断
	 */
	void hangup(int isActive);
	void sendMsg(string toId, string msg);
	void sendControlMsg(int msgType);
	virtual void voipStopOK(int stopType);
	//服务端收到calling请求，此时客户端可以通过消息系统通知对方
	virtual void voipCallingAck();
	//calling失败
	virtual void voipCallingFailed(char* errString);
	//接收方准备好，可以开始插入数据
	virtual void voipResponseOk();
	//response失败
	virtual void voipResponseFailed(char* errString);
	//发送方准备好，可以开始插入数据
	virtual void voipCallingOk();
	virtual int voipError(char* errString);
	virtual int voipSpeedTestFinish(char* userIp, int uploadVariance, int uploadSpeed, int downloadVariance, int downSpeed);
	virtual int voipEchoTestFinish(int index, int len, int timeCost);
	virtual int voipGetRealtimeData(uint8_t* data, int len);
	virtual int reportVoipTransState(int state);
	void insertAudioRaw(uint8_t* audioData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	// msg callback
	virtual void onNewMessage(CIMMessage* var1);
	virtual void onSendMessageSuccess(int msgIndex);
	virtual void onSendMessageFailed(int msgIndex);

	void querySoundData(uint8_t** pData, int* nLength);
private:
	IVoipManagerListener* m_pVoipManagerListener;
	CChatManager* m_pChatManager;
	CCodecManager* m_pCodecManager;
	CUserManager* m_pUserManager;
	IResultCallback* m_pResultCallback;
	string m_strTargetId;
	map<string, string> m_RecvControlMsg;
	static bool m_bCalling;
	bool m_bInit;
	int m_nServerPort;
};

