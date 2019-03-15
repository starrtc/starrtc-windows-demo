#pragma once
#include <string>
using namespace std;

class IStarVoipP2PListener 
{
public:
	/**
	 * 初始化成功
	 */
	virtual void initComplete(bool success) = 0;

	virtual void callingOK() = 0;
	virtual void callingFailed(string error) = 0;
	virtual void responseOK() = 0;
	virtual void responseFailed(string error) = 0;

	/**
	 * 被呼叫
	 */
	virtual void onCalling(string farIP) = 0;

	/**
	 * 被拒接
	 */
	virtual void onRefused(string farIP) = 0;

	/**
	 * 被挂断
	 */
	virtual void onHangup(string farIP) = 0;

	/**
	 * 占线
	 */
	virtual void onBusy(string farIP) = 0;

	/**
	 * 接通
	 */
	virtual void onConnect(string farIP) = 0;

	/**
	 * 报错
	 */
	virtual void onError(string code) = 0;

	/**
	 * 已关闭
	 */
	virtual void onStop(string code) = 0;

	/**
	 * 收到实时数据
	 */
	virtual void onRevRealtimeData(uint8_t* bytes, int length) = 0;

	virtual void onP2PConnectSuccess() = 0;
	virtual void onP2PConnectFailed() = 0;
};