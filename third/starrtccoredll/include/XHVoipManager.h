#pragma once
#include "IVoipManagerListener.h"
#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif
class MATH_API XHVoipManager
{
public:
	XHVoipManager(IVoipManagerListener* pVoipManagerListener);
	virtual ~XHVoipManager();
public:
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
	
	void insertAudioRaw(uint8_t* audioData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);	
	void querySoundData(uint8_t** pData, int* nLength);

};

