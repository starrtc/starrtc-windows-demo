#pragma once
#include "CIMMessage.h"
class IStarVoipListener 
{
public:
	//发送方准备好，可以开始插入数据
	virtual void voipCallingOk() = 0;
	//calling失败
	virtual void voipCallingFailed(char* errString) = 0;
	//接收方准备好，可以开始插入数据
	virtual void voipResponseOk() = 0;
	//response失败
	virtual void voipResponseFailed(char* errString) = 0;

	virtual void voipStopOK(int stopType) = 0;
	//服务端收到calling请求，此时客户端可以通过消息系统通知对方
	virtual void voipCallingAck() = 0;

	virtual int voipError(char* errString) = 0;
	virtual int voipSpeedTestFinish(char* userIp, int uploadVariance, int uploadSpeed, int downloadVariance, int downSpeed) = 0;
	virtual int voipEchoTestFinish(int index, int len, int timeCost) = 0;
	virtual int voipGetRealtimeData(uint8_t* data, int len) = 0;
	virtual int reportVoipTransState(int state) = 0;
};
