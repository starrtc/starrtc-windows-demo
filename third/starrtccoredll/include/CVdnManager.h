#pragma once
#include "ILiveInterface.h"
#include "IVdnListener.h"
#include "IVdnManagerListener.h"
#include "IRecvDataListener.h"
class CVdnManager : public ILiveInterface, public IRecvDataListener, virtual public IVdnListener
{
public:
	CVdnManager(CUserManager* pUserManager, IVdnManagerListener* pVdnManagerListener);
	virtual ~CVdnManager();

	/*
	 * 通过调度获取Channel服务地址
	 */
	virtual bool getApplyDownloadChannelServerAddr();

	/*
	 * Channel 申请下载
	 */
	bool applyDownload();

	/*
	 * Channel 停止下载
	 */
	bool stopLiveDownload();

	/*
	 * 设置数据流配置
	 */
	virtual bool setStreamConfig(int upId, bool isBig);
	virtual void querySoundData(uint8_t** pData, int* nLength);
	virtual int applyDownloadChannelOK();
	virtual int applyDownloadChannelFailed(char* errString);
	virtual int downloadChannelError(char* errString);
	virtual int downloadStopOK();
	virtual int downloadChannelClosed();
	virtual int downloadChannelLeave();
	virtual int downloadNetworkUnnormal();
	virtual int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum);
	virtual int uploaderAdd(char* upUserId, int upId);
	virtual int uploaderRemove(char* upUserId, int upId);
	virtual int downloadStreamConfigOK(char* channelId);
	virtual int downloadStreamConfigFailed();
	virtual int getRealtimeData(int upId, uint8_t* data, int len);
	virtual int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen);
public:
	string m_strApplyDownloadChannelServerIp;
	int m_nApplyDownloadChannelServerPort;
	bool m_bApplayDownload;
	IVdnManagerListener* m_pVdnManagerListener;
};

