#pragma once
#include "IStarVoipP2PListener.h"
#include "IVoipP2PManagerListener.h"
#include "IRecvDataListener.h"
#include "CCodecManager.h"
#include <map>
using namespace std;
class CVoipP2PManager : public IStarVoipP2PListener, public IRecvDataListener
{
public:
	CVoipP2PManager(CUserManager* pUserManager, IVoipP2PManagerListener* pVoipManagerListener);
	virtual ~CVoipP2PManager();
public:
	void setUserId(string strUserId);
	int init();
	void stopVoip();

	/**
	 * 设置媒体类型（音视频，音频，视频 三种可选）
	 * @param mediaTypeEnum 媒体类型
	 */
	void setRtcMediaType(int mediaTypeEnum);

	/**
	 * 获取媒体类型（音视频，音频，视频 三种可选）
	 */
	int getRtcMediaType();
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
	void sendControlMsg(int msgType, string strTargetId);

	/**
	 * 报错
	 */
	virtual void onError(string code);

	/**
	 * 已关闭
	 */
	virtual void onStop(string code);

	/**
	 * 收到实时数据
	 */
	virtual void onRevRealtimeData(uint8_t* bytes, int length);

	virtual void onP2PConnectSuccess();
	virtual void onP2PConnectFailed();

	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceiveMessage(CIMMessage* pMessage);

	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	void insertAudioRaw(uint8_t* audioData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	
	void querySoundData(uint8_t** pData, int* nLength);
private:
	IVoipP2PManagerListener* m_pVoipManagerListener;
	CCodecManager* m_pCodecManager;
	CUserManager* m_pUserManager;
	string m_strTargetId;
	string m_strUserId;
	map<string, string> m_RecvControlMsg;
	bool m_bCalling;
	bool m_bBusy;
	bool m_bInit;
	int m_nServerPort;
};

