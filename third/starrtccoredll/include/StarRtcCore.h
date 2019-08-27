#pragma once

#ifndef MATH_API
#define MATH_API _declspec(dllexport)
#endif

#include "IStarIMC2CListener.h"
#include "IStarIMChatroomListener.h"
#include "IVdnListener.h"
#include "ISrcListener.h"
#include "IGroupListener.h"
#include "IStarVoipListener.h"
#include "IStarVoipP2PListener.h"
#include "IRecvDataListener.h"
#include "IChatroomGetListListener.h"
#include "ILoginListener.h"
/*
 * StarRtc接口类
 */
class StarRtcCore
{
private:
	/*
	 * 构造函数
	 * @param pUserManager 用户配置信息
	 */
	StarRtcCore();
	
public:

	/*
	 * 获取StarRtc接口对象
	 * @param pUserManager 用户配置信息
	 */
	static StarRtcCore* getStarRtcCoreInstance();
	
	/*
	 * 析构函数
	 */
	~StarRtcCore();

	/*
	 * 注册回调函数
	 */
	void registerCallback();

	/*
	 * 申请内存
	 */
	void starRTCMalloc(uint8_t** outPtr, int length);

	/*
	 * 释放内存
	 */
	void starRTCFree(uint8_t* ptr);


	void setLogFile(char *dir);

	void saveFile(int save_mode);

	void setconfigLog(int log_level, int log_filter, int log_freq);
	/**
	 * 添加IM监听
	 * @param listener
	 */
	void addLoginListener(ILoginListener* listener);
	
	/**
	 * 添加获取列表监听
	 * @param listener
	 */
	void addGetListListener(IChatroomGetListListener* listener);

	/**
	 * 添加C2C消息监听
	 * @param listener
	 */
	void addC2CListener(IStarIMC2CListener* listener);

	/**
	 * 添加group消息监听
	 * @param listener
	 */
	void addGroupListener(IGroupListener* listener);

	/**
	 * 添加StarIMChatroom消息监听
	 * @param listener
	 */
	void addStarIMChatroomListener(IStarIMChatroomListener* listener);

	/**
	 * 添加Vdn消息监听
	 * @param listener
	 */
	void addVdnListener(IVdnListener* pVdnListener);

	/**
	 * 添加Src消息监听
	 * @param listener
	 */
	void addSrcListener(ISrcListener* pSrcListener);

	/**
	 * 添加Voip监听
	 * @param listener
	 */
	void addVoipListener(IStarVoipListener* listener);

	/**
	 * 添加VoipP2P监听
	 * @param listener
	 */
	void addVoipP2PListener(IStarVoipP2PListener* listener);

	/**
	 * 添加RecvData监听
	 * @param listener
	 */
	void addRecvDataListener(IRecvDataListener* listener);

	/**
	 * 启动IM服务
	 */
	bool startIMServer(char* servIP, int servPort, char* agentId, char* userId, char* starToken);

	/**
	 * 停止IM服务
	 */
	bool stopIMServer();

	/**
	 * 发送消息
	 */
	bool sendMessage(CIMMessage* pIMMessage);

	/**
	 * 发送上线消息
	 */
	bool sendOnlineMessage(CIMMessage* pIMMessage);

	/**
	 * 发送群组消息
	 */
	int sendGroupMsg(CIMMessage* pIMMessage);

	/**
	 * 获取群组列表
	 */
	int applyGetGroupList();
	/**
	 * 获取群组用户列表
	 */
	int  applyGetUserList(char* groupId);
	
	/**
	 * 申请创建群组
	 */
	int applyCreateGroup(char* addUsers, char* userDefineData);
	
	/**
	 * 申请删除
	 */
	int applyDelGroup(char* groupId);

	/**
	 * 申请向群组添加用户
	 */
	int applyAddUserToGroup(char* groupId, char* addUsers, char* userDefineData);
	
	/**
	 * 申请移除群组用户
	 */
	int applyRemoveUserToGroup(char* groupId, char* removeUsers);
	
	/**
	 * 发送系统消息给指定用户
	 */
	int sendSystemMsgToUser(char* sendUsers, int msgDataType, char* msgStr, char* msgDigest);
	
	/**
	 * 发送系统消息给群组
	 */
	int sendSystemGroupMsg(char* groupId, int msgDataType, char* msgStr, char* msgDigest);
	
	/**
	 * 申请忽略群组消息
	 */
	int applySetGroupPushIgnore(char* groupId);
	
	/**
	 * 申请取消忽略群组消息
	 */
	int applyUnsetGroupPushIgnore(char* groupId);
	
	/**
	 * 设置推送模式
	 */
	int setPushMode(char* pushMode);
	
	/**
	 * 获取推送模式
	 */
	int getPushMode();

	int queryAllChatRoomList(char* servAddr, int servPort, char* userId, char* listType);
	
	int saveToChatRoomList(char* servAddr, int servPort, char* userId, int listType, char* roomId, char* data);
	
	int delFromChatRoomList(char* servAddr, int servPort, char* userId, int listType, char* roomId);

	/*
	 * 创建ChatRoom
	 */
	bool createChatRoom(string serverIp, int serverPort, string strName, int chatroomType, string strAgentId, string strUserId, string strTokenId);

	/*
	 * 加入ChatRoom
	 */
	bool joinChatRoom(string serverIp, int serverPort, string strChatroomId, string strAgentId, string strUserId, string strTokenId);

	/*
	 * 查询chatroom在线人数
	 */
	bool getOnlineNumber(string strChatroomId);

	bool banToSendMsg(char* banUserId, int banTime);
	bool kickOutUser(char* kickOutUserId);
	bool sendChat(CIMMessage* pIMMessage);
	bool sendPrivateChat(char* targetId, CIMMessage* pIMMessage);
	bool deleteChatRoom();

	/*
	 *  与ChatRoom断开连接
	 */
	bool stopChatRoomConnect();

	//==================================voip====================================
	int startVoipEncoder(int audioSampleRateInHz, int audioChannels, int audioBitRate, int rotation);
	void voipCalling(char* servAddr, int servPort, char* agentId, char* userId, char* starToken, char* responserUserId);
	void voipResponse(char* servAddr, int servPort, char* agentId, char* userId, char* starToken, char* callerUserId);
	void stopVoip(int isActive);//主动关闭一方传1   被动关闭一方传0  
	void voipSpeedTest(char* servIp, int port);
	void voipEchoTest(char* servIp, int port);

	void initStarVoipDirectLink();
	void stopStarVoipDirectLink();
	// 按照这个顺序执行 :interface_connectFarVoip-interface_startTransVoipData-interface_startVoipDirectLinkEncoder-interface_closeFarVoip
	void connectFarVoip(char* farUrl_c);
	void startTransVoipData();
	int  startVoipDirectLinkEncoder(int audioSampleRateInHz, int audioChannels, int audioBitRate, int rotation);
	void closeFarVoip();
	void sendMsgDataToFar(CIMMessage* pIMMessage);

	/*
	 * Channel 申请下载
	 */
	bool applyDownload(string serverIp, int port, string channelId, string strAgentId, string strUserId, string strTokenId);

	/*
	 * Channel 停止下载
	 */
	bool stopDownload();

	/*
	 * 设置数据流配置
	 */
	bool setStreamConfigVdn(int* sendBuf, int length);

	void setGlobalSetting(int videoEnable, int audioEnable,
		int videoBigIsHw,
		int videoBigWidth, int videoBigHeight, int videoBigFps, int videoBigBitrate,
		int videoSmallWidth, int videoSmallHeight, int videoSmallFps, int videoSmallBitrate,
		int openGLESEnable, int dynamicBitrateAndFpsEnable, int voipP2PEnable);

	void setRuntimeAudioEnable(int audioEnable);
	void setRuntimeVideoEnable(int videoEnable);
	/*
	 * 设置数据流配置
	 */
	bool setStreamConfigSrc(int* sendBuf, int length);
	//int queryAllChannelList(char* servAddr, int servPort, char* userId, char* listType);

	/*
	 * 创建Channel
	 */
	bool createPublicChannel(string strServerIp, int port, string strName, int listType, string strChatroomId, string strAgentId, string strUserId, string strTokenId);
	
	/*
	 * 创建Channel
	 */
	bool starLiveCreateLoginChannel(string strServerIp, int servPort, string strName, int listType, string strChatroomId, string strAgentId, string strUserId, string strTokenId);

	bool createBroadcastChannel(string strServerIp, int port, string strName, int listType, string strChatroomId, string strAgentId, string strUserId, string strTokenId);
	int startLiveSrcEncoder(int audioSampleRateInHz, int audioChannels, int audioBitRate, int rotation);
	int startUploadSrcServer(char* servAddr, int servPort, char* agentId, char* userId, char* starToken, char* channelId/* ,int maxAudioPacketNum,int maxVideoPacketNum */);
	void setUploader(char* userId);
	
	int stopUploadSrcServer();
	int stopLiveSrcCodec(int disable_decoder);

	void insertAudioRaw(uint8_t* audioData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoNalu(uint8_t* videoData, int dataLen);
	//videoData的释放由此函数负责
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	//裁剪视频并生成小图,outVideoDataBig与outVideoDataSmall在函数内malloc,由ios自己free，若无小图，则outVideoDataSmall指向的为NULL
	//videoData由在函数内释放
	//成功返回0，失败返回-1
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	//realtimeData的释放由此函数负责
	void insertRealtimeData(uint8_t* realtimeData, int dataLen);
	void querySoundData(uint8_t** pData, int* nLength);
	//=========================================================================
	//===========================    Msg回调    ===========================
	//=========================================================================
	/**
	 * msgServer错误,这个函数是新线程调用
	 */
	static int msgErr(char* errString, void* userData);

	/**
	 * 重试多次后仍不能连接到msgServer，或用户主动调用stop后回调
	 */
	static int stop(void* userData);

	/**
	 * msgServer处于在线状态
	 */
	static int online(int maxContentLen, void* userData);

	/**
	 * msgServer中断状态
	 */
	static int offline(void* userData);

	/**
	 * 发送消息的群信息还未同步完成，等待5秒再试
	 */
	static int groupIsSyncing(char* groupId, void* userData);

	/**
	 * 收到单聊消息发送成功反馈
	 */
	static int sendMsgFin(int msgIndex, char* toUserId, uint32_t time, void* userData);

	/**
	 * 收到单聊消息
	 */
	static int getNewMsg(char* fromUserId, uint32_t time, char* msgData, void* userData);

	/**
	 * 收到群消息
	 */
	static int getNewGroupMsg(char* groupId, char* fromUserId, uint32_t time, char* msgData, void* userData);

	/**
	 * 收到群推送消息
	 */
	static int getGroupSystemMsg(char* groupId, uint32_t time, char* msgData, void* userData);

	/**
	 * 收到系统推送消息
	 */
	static int getSystemMsg(uint32_t time, char* msgData, void* userData);

	/**
	 * 下面几个函数的status参数为返回状态字
	 * status常见字串:
	 * AECERRID_AEC_AUTH_FAILED, //AEC鉴权失败
	 * AECERRID_AEC_URL_CONNECT_FAILED, //AEC url连接失败
	 * AECERRID_AEC_RESPONSE_JSON_PARSE_ERR, //AEC返回的json格式解析错误
	 * GROUPPUSH_ERRID_GROUPID_IS_SYNCING
	 * GROUPPUSH_ERRID_USERID_IS_NOT_IN_GROUP, //此用户不在指定的群内
	 * 收到群消息发送成功反馈
	 */
	static int sendGroupMsgFin(char* status, int groupMsgIndex, char* groupId, uint32_t time, void* userData);
	static int applyCreateGroupFin(char* status, int reqIndex, char* groupId, void* userData);
	static int applyDelGroupFin(char* status, int reqIndex, char* groupId, void* userData);

	//ray0306-3
	static int applyGetGroupListFin(char* status, int reqIndex, char* groupIdList, char* groupNameList, char* creatorList, void* userData);
	static int applyGetUserListFin(char* status, int reqIndex, int isIgnore, char* userIdList, void* userData);

	//ray0306-3


	static int applyAddUserToGroupFin(char* status, int reqIndex, char* groupId, void* userData);
	static int applyRemoveUserFromGroupFin(char* status, int reqIndex, char* groupId, void* userData);
	static int sendSystemMsgToUserFin(char* status, int reqIndex, void* userData);
	static int sendSystemGroupMsgFin(char* status, int reqIndex, char* groupId, void* userData);
	static int setPushModeOK(void* userData);
	static int setPushModeFailed(void* userData);
	static int getPushMode(char* pushMode, void* userData);
	static int setPushIgnoreFin(char* status, char* groupId, void* userData);
	static int unsetPushIgnoreFin(char* status, char* groupId, void* userData);
	static int msg_getAllUserListOk(int totalPageNum, int reqPageNum, char* userIdList, void* userData);
	static int msg_getAllUserListFailed(int totalPageNum, int reqPageNum, void* userData);
	static int msg_getAliveNum(int userCount, int totalPageNum, void* userData);
	//=========================================================================
	//===========================    Voip回调    ===========================
	//=========================================================================
	static void voipStopOK(void* userData, int stopType);
	//服务端收到calling请求，此时客户端可以通过消息系统通知对方
	static void voipCallingAck(void* userData);
	//calling失败
	static void voipCallingFailed(char* errString, void* userData);
	//接收方准备好，可以开始插入数据
	static void voipResponseOk(void* userData);
	//response失败
	static void voipResponseFailed(char* errString, void* userData);
	//发送方准备好，可以开始插入数据
	static void voipCallingOk(void* userData);
	static int voipError(char* errString, void* userData);
	static int voipSpeedTestFinish(char* userIp, int uploadVariance, int uploadSpeed, int downloadVariance, int downSpeed, void* userData);
	static int voipEchoTestFinish(int index, int len, int timeCost, void* userData);
	static int voipGetRealtimeData(uint8_t* data, int len, void* userData);
	// 1是p2p, 2是中转
	static int reportVoipTransState(int state, void* userData);
	//=============================    voip direct回调    ============================
	static void connectFarVoipOK(void* userData);
	static void connectFarVoipFailed(void* userData);
	static void starVoipDirectLinkError(char* errString, void* userData);
	static void voipDirectLinkRecvMsg(char* msg, void* userData);
	//=========================================================================
	//===========================    live chatroom回调    ===========================
	//=========================================================================
	static int createChatroomOK(char* roomId, int maxContentLen, void* userData);

	static int createChatroomFailed(void* userData, char* errString);

	static int joinChatroomOK(char* roomId, int maxContentLen, void* userData);

	static int joinChatroomFailed(char* roomId, char* errString, void* userData);

	static int chatroomError(char* errString, void* userData);

	static int chatroomStop(void* userData);

	static int chatroomQueryAllListOK(char* listData, void* userData);

	static int deleteChatroomOK(char* roomId, void* userData);
	static int deleteChatroomFailed(char* roomId, char* errString, void* userData);

	static int chatroomBanToSendMsgOK(char* banUserId, int banTime, void* userData);
	static int chatroomBanToSendMsgFailed(char* banUserId, int banTime, char* errString, void* userData);

	static int chatroomKickOutOK(char* kickOutUserId, void* userData);
	static int chatroomKickOutFailed(char* kickOutUserId, char* errString, void* userData);

	//被禁言
	static int chatroomSendMsgBanned(unsigned int remainTimeSec, void* userData);
	//被踢出房间
	static int chatroomKickedOut(void* userData);
	//收到消息
	static int chatroomGetNewMsg(char* fromUserId, char* msgData, void* userData);
	//收到私信消息
	static int chatroomGetNewPrivateMsg(char* fromUserId, char* msgData, void* userData);
	//收到房间人数信息
	static int chatroomGetRoomOnlineNumber(char* roomId, int onlineNum, void* userData);
	//消息发送失败，余额不足
	static int chatroomSendMsgNoFee(void* userData);

	//新加接口
	static int chatroomSaveToChatRoomListOK(char* roomId, void* userData);
	static int chatroomSaveToChatRoomListFailed(char* roomId, void* userData);
	static int chatroomDelFromChatRoomListOK(char* roomId, void* userData);
	static int chatroomDelFromChatRoomListFailed(char* roomId, void* userData);

	//=========================================================================
	//===========================    liveVdn回调    ===========================
	//=========================================================================

	static int applyDownloadChannelOK(void* userData);
	static int applyDownloadChannelFailed(char* errString, void* userData);
	static int downloadChannelError(char* errString, void* userData);

	static int downloadStopOK(void* userData);
	static int downloadChannelClosed(void* userData);
	static int downloadChannelLeave(void* userData);

	static int downloadNetworkUnnormal(void* userData);
	static int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum, void* userData);
	static int uploaderAdd(char* upUserId, int upId, void* userData);
	static int uploaderRemove(char* upUserId, int upId, void* userData);
	static int downloadStreamConfigOK(char* channelId, void* userData);
	static int downloadStreamConfigFailed(void* userData);
	static int getRealtimeData(int upId, uint8_t* data, int len, void* userData);

	//=========================================================================
	//===========================    liveSrc回调    ===========================
	//=========================================================================
	static int createChannelOK(char* channelId, void* userData);
	static int createChannelFailed(char* errString, void* userData);

	static int applyUploadChannelOK(char* channelId, void* userData);
	static int applyUploadChannelFailed(char* errString, char* channelId, void* userData);

	static int setUploaderOK(char* channelId, char* uploadUserId, void* userData);
	static int setUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData);

	static int unsetUploaderOK(char* channelId, char* uploadUserId, void* userData);
	static int unsetUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData);

	static int muteUploaderOK(char* channelId, char* uploadUserId, void* userData);
	static int muteUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData);

	static int unmuteUploaderOK(char* channelId, char* uploadUserId, void* userData);
	static int unmuteUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData);

	static int deleteChannelOK(char* channelId, void* userData);
	static int deleteChannelFailed(char* errString, char* channelId, void* userData);

	static int uploadUnseted(char* channelId, void* userData);
	static int uploadMuted(char* channelId, void* userData);
	static int uploadUnmuted(char* channelId, void* userData);

	static int setPeerStreamDownloadConfigOK(char* channelId, void* userData);
	static int setPeerStreamDownloadConfigFailed(char* channelId, void* userData);

	static int stopOK(void* userData);
	static int isRetrying(void* userData);
	static int networkUnnormal(void* userData);

	static int srcError(char* errString, void* userData);
	static int querySrcChannelOnlineNumberFin(char* channelId, int totalOnlineNum, void* userData);

	static int uploaderAddSrc(char* upUserId, int upId, void* userData);
	static int uploaderRemoveSrc(char* upUserId, int upId, void* userData);
	static int getRealtimeDataSrc(int upId, uint8_t* data, int len, void* userData);
	
	//新加
	static int pushRtmpOKSrc(char* channelId, void* userData);
	static int pushRtmpFailedSrc(char* errString, char* channelId, void* userData);
	static int stopPushRtmpOKSrc(char* channelId, void* userData);
	static int stopPushRtmpFailedSrc(char* errString, char* channelId, void* userData);
	//static int channelQueryAllListOK(char* listData, void* userData);
	
	static int getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen, void* userData);
private:
	ILoginListener* m_pLoginListener;
	IChatroomGetListListener* m_pGetListListener;
	IStarIMC2CListener* m_pc2cMsgListener;
	IGroupListener* m_pGroupMsgListener;
	IStarIMChatroomListener *m_pStarIMChatroomListener;
	IVdnListener* m_pVdnListener;
	ISrcListener* m_pSrcListener;
	IStarVoipListener* m_pStarVoipListener;
	IStarVoipP2PListener* m_pStarVoipP2PListener;
	IRecvDataListener* m_pRecvDataListener;
	int m_groupReqIndex;
};
