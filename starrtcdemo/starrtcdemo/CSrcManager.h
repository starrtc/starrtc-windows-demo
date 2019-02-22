#pragma once
#include "ILiveInterface.h"
#include "ISrcListener.h"
#include "ISrcManagerListener.h"
class CSrcManager : public ILiveInterface, public ISrcListener
{
public:
	CSrcManager(CUserManager* pUserManager, ISrcManagerListener* pSrcManagerListener);
	virtual ~CSrcManager();

public:

	/*
	 * 全局参数设置
	 */
	void globalSetting(int w, int h, int fps, int bitrate);
	/*
	 * 通过调度获取ChatRoom服务地址
	 */
	bool getChannelServerAddr();

	/*
	 * 创建Channel
	 */
	bool createChannel(string strName, int channelType, string strChatroomId);

	/*
	 * Channel 申请上传
	 */
	bool applyUpload();

	/*
	 * 上报chatroom 和 channelID
	 */
	bool reportChatRoomAndChannel(string strName, string strChatroomId);
	/*
	 * 开启直播编码器
	 */
	bool startEncoder();

	/*
	 * Channel 停止上传
	 */
	bool stopUpload();

	/*
	 *  停止直播编码器
	 */
	bool stopEncoder();

	bool stop();
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
};

