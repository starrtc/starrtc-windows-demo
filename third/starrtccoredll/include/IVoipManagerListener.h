#pragma once
#include <string>
using namespace std;
#include "CIMMessage.h"
class IVoipManagerListener
{
public:
	/**
	 * 被叫方响应
	 * 被叫方收到主叫方的呼叫
	 * @param fromID
	 */
	virtual void onCalling(string fromID) = 0;

	/**
	 * 被叫方响应
	 * 主叫方在被叫方接听之前挂断（通话被取消）
	 * @param fromID
	 */
	virtual void onCancled(string fromID) = 0;

	/**
	 * 主叫方响应
	 * 被叫方拒绝接通（通话被拒绝）
	 * @param fromID
	 */
	virtual void onRefused(string fromID) = 0;

	/**
	 * 主叫方响应
	 * 被叫方线路忙（对方通话中）
	 * @param fromID
	 */
	virtual void onBusy(string fromID) = 0;

	/**
	 * 通话中错过的来电
	 */
	virtual void onMiss(CIMMessage* pMsg) = 0;

	/**
	 * 主叫方响应
	 * 被叫方接通（通话开始）
	 * @param fromID
	 */
	virtual void onConnected(string fromID) = 0;

	/**
	 * 对方已经挂断
	 * @param fromID
	 */
	virtual void onHangup(string fromID) = 0;

	/**
	 * voip报错
	 * @param errorCode
	 */
	virtual void onError(string errorCode) = 0;

	/**
	 * 收到实时数据
	 * @param data
	 */
	virtual void onReceiveRealtimeData(uint8_t* data, int length) = 0;

	/**
	 * 收到视频数据
	 * @param data
	 */
	virtual int getVideoRaw(string strUserId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;
	
	/**
	* 数据传输模式切换
	* @param state
	*/
	virtual void onTransStateChanged(int state) = 0;
};

