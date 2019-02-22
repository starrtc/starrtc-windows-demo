#pragma once
class  ISrcListener
{
public:
	virtual int createChannelOK(char* channelId) = 0;
	virtual int createChannelFailed(char* errString) = 0;

	virtual int applyUploadChannelOK(char* channelId) = 0;
	virtual int applyUploadChannelFailed(char* errString, char* channelId) = 0;

	virtual int setUploaderOK(char* channelId, char* uploadUserId) = 0;
	virtual int setUploaderFailed(char* errString, char* channelId, char* uploadUserId) = 0;

	virtual int unsetUploaderOK(char* channelId, char* uploadUserId) = 0;
	virtual int unsetUploaderFailed(char* errString, char* channelId, char* uploadUserId) = 0;

	virtual int muteUploaderOK(char* channelId, char* uploadUserId) = 0;
	virtual int muteUploaderFailed(char* errString, char* channelId, char* uploadUserId) = 0;

	virtual int unmuteUploaderOK(char* channelId, char* uploadUserId) = 0;
	virtual int unmuteUploaderFailed(char* errString, char* channelId, char* uploadUserId) = 0;

	virtual int deleteChannelOK(char* channelId) = 0;
	virtual int deleteChannelFailed(char* errString, char* channelId) = 0;

	virtual int uploadUnseted(char* channelId) = 0;
	virtual int uploadMuted(char* channelId) = 0;
	virtual int uploadUnmuted(char* channelId) = 0;

	virtual int setPeerStreamDownloadConfigOK(char* channelId) = 0;
	virtual int setPeerStreamDownloadConfigFailed(char* channelId) = 0;

	virtual int stopOK() = 0;
	virtual int isRetrying() = 0;
	virtual int networkUnnormal() = 0;

	virtual int srcError(char* errString) = 0;
	virtual int querySrcChannelOnlineNumberFin(char* channelId, int totalOnlineNum) = 0;

	virtual int uploaderAddSrc(char* upUserId, int upId) = 0;
	virtual int uploaderRemoveSrc(char* upUserId, int upId) = 0;
	virtual int getRealtimeDataSrc(int upId, uint8_t* data, int len) = 0;

	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen) = 0;
};