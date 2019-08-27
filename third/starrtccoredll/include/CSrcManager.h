#pragma once
#include "ILiveInterface.h"
#include "ISrcListener.h"
#include "ISrcManagerListener.h"
#include "CCodecManager.h"
#include "IRecvDataListener.h"
class CSrcManager : public ILiveInterface, virtual public ISrcListener, public IRecvDataListener
{
public:
	CSrcManager(CUserManager* pUserManager, ISrcManagerListener* pSrcManagerListener);
	virtual ~CSrcManager();

public:
	/*
	 * 获取channel列表
	 * @param pUserManager 用户信息
	 * @param listType 类型
	 */
	//static void getChannelList(CUserManager* pUserManager, string strUserId, int listType);

	/*
	 * 全局参数设置
	 */
	void globalSetting(int fps, int bitrate);
	void setRuntimeAudioEnable(int audioEnable);
	void setRuntimeVideoEnable(int videoEnable);
	/*
	 * 设置数据流配置
	 */
	virtual bool setStreamConfig(int upId, bool isBig);
	virtual void querySoundData(uint8_t** pData, int* nLength);
	virtual void insertRealtimeData(uint8_t* realtimeData, int dataLen);
	/*
	 * 通过调度获取ChatRoom服务地址
	 */
	bool getChannelServerAddr();

	/*
	 * 创建Channel
	 */
	bool createChannel(string strName, string strChatroomId);

	/*
	 * 创建Channel
	 */
	bool createLoginChannel(string strName, string strChatroomId);

	/*
	 * 创建Channel
	 */
	bool createBroadcastChannel(string strName, string strChatroomId);

	/*
	 * Channel 申请上传
	 */
	bool applyUpload();

	/*
	 * 开启直播编码器
	 */
	bool startEncoder(int audioSampleRateInHz, int audioChannels, int audioBitRate, int rotation);

	void setUploader(string strUserId);

	/*
	 * Channel 停止上传
	 */
	bool stopUpload();

	/*
	 *  停止直播编码器
	 */
	bool stopEncoder(int disable_decoder);

	bool stop();
	void insertAudioRaw(uint8_t* audioData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);

public:
	virtual int createChannelOK(char* channelId);
	virtual int createChannelFailed(char* errString);

	virtual int applyUploadChannelOK(char* channelId);
	virtual int applyUploadChannelFailed(char* errString, char* channelId);

	virtual int setUploaderOK(char* channelId, char* uploadUserId);
	virtual int setUploaderFailed(char* errString, char* channelId, char* uploadUserId);

	virtual int unsetUploaderOK(char* channelId, char* uploadUserId);
	virtual int unsetUploaderFailed(char* errString, char* channelId, char* uploadUserId);

	virtual int muteUploaderOK(char* channelId, char* uploadUserId);
	virtual int muteUploaderFailed(char* errString, char* channelId, char* uploadUserId);

	virtual int unmuteUploaderOK(char* channelId, char* uploadUserId);
	virtual int unmuteUploaderFailed(char* errString, char* channelId, char* uploadUserId);

	virtual int deleteChannelOK(char* channelId);
	virtual int deleteChannelFailed(char* errString, char* channelId);

	virtual int uploadUnseted(char* channelId);
	virtual int uploadMuted(char* channelId);
	virtual int uploadUnmuted(char* channelId);

	virtual int setPeerStreamDownloadConfigOK(char* channelId);
	virtual int setPeerStreamDownloadConfigFailed(char* channelId);

	virtual int stopOK();
	virtual int isRetrying();
	virtual int networkUnnormal();

	virtual int srcError(char* errString);
	virtual int querySrcChannelOnlineNumberFin(char* channelId, int totalOnlineNum);

	virtual int uploaderAddSrc(char* upUserId, int upId);
	virtual int uploaderRemoveSrc(char* upUserId, int upId);
	virtual int getRealtimeDataSrc(int upId, uint8_t* data, int len);

	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);
private:
	string m_strApplyUploadChannelServerIp;
	int m_nApplyUploadChannelServerPort;
	bool m_bApplyUpload;
	ISrcManagerListener* m_pSrcManagerListener;

	CCodecManager* m_pCodecManager;
};

