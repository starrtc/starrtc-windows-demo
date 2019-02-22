#include "stdafx.h"
#include "StarRtcCore.h"
#include "IStarIMC2CListener.h"
#include "IErrorCallback.h"
#include "interface_starLiveVideo.h"
#include "StarIMMessageType.h"
#include "CMsgUtil.h"

StarRtcCore* g_pStarRtcCore = NULL;
//StarRtcCore* StarRtcCore::m_pStarRtcCore = NULL;
StarRtcCore::StarRtcCore(CUserManager* pUserManager)
{
	m_pUserManager = pUserManager;
	m_pc2cMsgListener = NULL;
	m_pGroupMsgListener = NULL;
	m_pStarIMChatroomListener = NULL;
	m_pVdnListener = NULL;
	m_pSrcListener = NULL;
	m_groupReqIndex = 0;
	registerCallback();
}


StarRtcCore::~StarRtcCore()
{
	m_pc2cMsgListener = NULL;
	m_pGroupMsgListener = NULL;
	m_pStarIMChatroomListener = NULL;
	m_pVdnListener = NULL;
	m_pSrcListener = NULL;
}

StarRtcCore* StarRtcCore::getStarRtcCoreInstance(CUserManager* pUserManager)
{	
	if (g_pStarRtcCore == NULL)
	{
		g_pStarRtcCore = new StarRtcCore(pUserManager);
	}
	return g_pStarRtcCore;
	/*if (StarRtcCore::m_pStarRtcCore == NULL)
	{
		StarRtcCore::m_pStarRtcCore = new StarRtcCore(pUserManager);
	}
	return StarRtcCore::m_pStarRtcCore;*/
}

void StarRtcCore::registerCallback()
{
	callbackInit_Msg((fun_msg_msgErr)msgErr,
		(fun_msg_stop)stop,
		(fun_msg_online)online,
		(fun_msg_offline)offline,
		(fun_msg_groupIsSyncing)groupIsSyncing,
		(fun_msg_sendMsgFin)sendMsgFin,
		(fun_msg_sendGroupMsgFin)sendGroupMsgFin,
		//fun_msg_sendPrivateGroupMsgFin msg_sendPrivateGroupMsgFin,
		(fun_msg_getNewMsg)getNewMsg,
		(fun_msg_getNewGroupMsg)getNewGroupMsg,
		//fun_msg_getNewPrivateGroupMsg msg_getNewPrivateGroupMsg,
		(fun_msg_getGroupSystemMsg)getGroupSystemMsg,
		(fun_msg_getSystemMsg)getSystemMsg,
		(fun_msg_sendSystemMsgToUserFin)sendSystemMsgToUserFin,
		(fun_msg_sendSystemGroupMsgFin)sendSystemGroupMsgFin,
		(fun_msg_applyCreateGroupFin)applyCreateGroupFin,
		(fun_msg_applyDelGroupFin)applyDelGroupFin,
		(fun_msg_applyAddUserToGroupFin)applyAddUserToGroupFin,
		(fun_msg_applyRemoveUserFromGroupFin)applyRemoveUserFromGroupFin,
		(fun_msg_setPushModeOK)setPushModeOK,
		(fun_msg_setPushModeFailed)setPushModeFailed,
		(fun_msg_getPushMode)getPushMode,
		(fun_msg_setPushIgnoreFin)setPushIgnoreFin,
		(fun_msg_unsetPushIgnoreFin)unsetPushIgnoreFin,
		this);

	callbackInit_chatRoom(createChatroomOK,
		joinChatroomOK,
		createChatroomFailed,
		joinChatroomFailed,
		chatroomError,
		chatroomStop,
		deleteChatroomOK,
		deleteChatroomFailed,
		chatroomBanToSendMsgOK,
		chatroomBanToSendMsgFailed,
		chatroomKickOutOK,
		chatroomKickOutFailed,
		chatroomSendMsgBanned,
		chatroomKickedOut,
		chatroomGetNewMsg,
		chatroomGetNewPrivateMsg,
		chatroomGetRoomOnlineNumber,
		chatroomSendMsgNoFee,
		this);

	callbackInit_liveVideoVdn((fun_live_applyDownloadChannel_ok)applyDownloadChannelOK,
		(fun_live_applyDownloadChannel_failed)applyDownloadChannelFailed,
		(fun_live_downloadChannel_error)downloadChannelError,
		(fun_live_download_stop_ok)downloadStopOK,
		(fun_live_download_channel_closed)downloadChannelClosed,
		(fun_live_download_channel_leave)downloadChannelLeave,
		(fun_live_download_network_unnormal)downloadNetworkUnnormal,
		(fun_live_query_vdn_channel_online_number_fin)queryVDNChannelOnlineNumberFin,
		(fun_live_vdn_uploader_add)uploaderAdd,
		(fun_live_vdn_uploader_remove)uploaderRemove,
		(fun_live_set_download_stream_config_ok)downloadStreamConfigOK,
		(fun_live_set_download_stream_config_failed)downloadStreamConfigFailed,
		(fun_live_vdn_get_realtime_data)getRealtimeData,
		this);

	callbackInit_liveVideoSrc((fun_live_src_create_channel_ok)createChannelOK,
		(fun_live_src_create_channel_failed)createChannelFailed,
		(fun_live_src_apply_upload_channel_ok)applyUploadChannelOK,
		(fun_live_src_apply_upload_channel_failed)applyUploadChannelFailed,
		(fun_live_src_set_uploader_ok)setUploaderOK,
		(fun_live_src_set_uploader_failed)setUploaderFailed,
		(fun_live_src_unset_uploader_ok)unsetUploaderOK,
		(fun_live_src_unset_uploader_failed)unsetUploaderFailed,
		(fun_live_src_mute_uploader_ok)muteUploaderOK,
		(fun_live_src_mute_uploader_failed)muteUploaderFailed,
		(fun_live_src_unmute_uploader_ok)unmuteUploaderOK,
		(fun_live_src_unmute_uploader_failed)unmuteUploaderFailed,
		(fun_live_src_delete_channel_ok)deleteChannelOK,
		(fun_live_src_delete_channel_failed)deleteChannelFailed,
		(fun_live_src_upload_unseted)uploadUnseted,
		(fun_live_src_upload_muted)uploadMuted,
		(fun_live_src_upload_unmuted)uploadUnmuted,
		(fun_live_src_set_peer_stream_download_config_ok)setPeerStreamDownloadConfigOK,
		(fun_live_src_set_peer_stream_download_config_failed)setPeerStreamDownloadConfigFailed,
		(fun_live_src_stop_ok)stopOK,
		(fun_live_src_is_retrying)isRetrying,
		(fun_live_src_network_unnormal)networkUnnormal,
		(fun_live_src_error)srcError,
		(fun_live_query_src_channel_online_number_fin)querySrcChannelOnlineNumberFin,
		(fun_live_src_uploader_add)uploaderAdd,
		(fun_live_src_uploader_remove)uploaderRemove,
		(fun_live_src_get_realtime_data)getRealtimeData,
		this);

	callbackInit_starLiveVideo(getVideoRaw, this);
}

/**
 * 添加C2C消息监听
 * @param listener
 */
void StarRtcCore::addC2CListener(IStarIMC2CListener* listener)
{
	m_pc2cMsgListener = listener;
}

/**
 * 添加group消息监听
 * @param listener
 */
void StarRtcCore::addGroupListener(IGroupListener* listener)
{
	m_pGroupMsgListener = listener;
}

/**
 * 添加StarIMChatroom消息监听
 * @param listener
 */
void StarRtcCore::addStarIMChatroomListener(IStarIMChatroomListener* listener)
{
	m_pStarIMChatroomListener = listener;
}

/**
 * 添加Vdn消息监听
 * @param listener
 */
void StarRtcCore::addVdnListener(IVdnListener* pVdnListener)
{
	m_pVdnListener = pVdnListener;
}

/**
 * 添加Src消息监听
 * @param listener
 */
void StarRtcCore::addSrcListener(ISrcListener* pSrcListener)
{
	m_pSrcListener = pSrcListener;
}

bool StarRtcCore::startIMServer()
{
	//strIP = "101.200.44.42";
	printf("--------------logIn start-----------\n");
	int ret = interface_msgServerStart((char*)m_pUserManager->m_strIMServerIp.c_str(), m_pUserManager->m_nIMServerPort, (char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), (char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(), (char*)m_pUserManager->m_strTokenId.c_str());
	//printf("------------------login end ret:%d-------\n", ret);
	return true;
}

bool StarRtcCore::stopIMServer()
{
	//strIP = "101.200.44.42";
	printf("--------------logIn start-----------\n");
	interface_msgServerStop();
	//printf("------------------login end ret:%d-------\n", ret);
	return true;
}

bool StarRtcCore::sendMessage(CIMMessage* pIMMessage)
{
	string str = CMsgUtil::toJson(pIMMessage);
	interface_sendMsg(pIMMessage->m_nMsgIndex, (char*)pIMMessage->m_strTargetId.c_str(), MSG_SEND_TYPE_OFF_LINE_NO_PUSH, (char*)str.c_str(), (char*)"", 0);
	return true;
}

bool StarRtcCore::sendOnlineMessage(CIMMessage* pIMMessage)
{
	string str = CMsgUtil::toJson(pIMMessage);
	interface_sendMsg(pIMMessage->m_nMsgIndex, (char*)pIMMessage->m_strTargetId.c_str(), MSG_SEND_TYPE_ON_LINE_NO_PUSH, (char*)str.c_str(), (char*)"", 0);
	return true;
}

int StarRtcCore::sendGroupMsg(CIMMessage* pIMMessage)
{
	string str = CMsgUtil::toJson(pIMMessage);
	return interface_sendGroupMsg((char*)pIMMessage->m_strAtList.c_str(), pIMMessage->m_nMsgIndex, (char*)pIMMessage->m_strTargetId.c_str(), MSG_SEND_TYPE_OFF_LINE_NO_PUSH, (char*)str.c_str(), (char*)"", 0);
}

int StarRtcCore::applyCreateGroup(char* addUsers, char* userDefineData)
{
	return interface_applyCreateGroup(m_groupReqIndex++, addUsers, userDefineData);
}

int StarRtcCore::applyDelGroup(char* groupId)
{
	return interface_applyDelGroup(m_groupReqIndex++, groupId);
}

int StarRtcCore::applyAddUserToGroup(char* groupId, char* addUsers, char* userDefineData)
{
	return interface_applyAddUserToGroup(m_groupReqIndex++, groupId, addUsers, userDefineData);
}

int StarRtcCore::applyRemoveUserToGroup(char* groupId, char* removeUsers)
{
	return interface_applyRemoveUserToGroup(m_groupReqIndex++, groupId, removeUsers);
}

int StarRtcCore::sendSystemMsgToUser(char* sendUsers, int msgDataType, char* msgStr, char* msgDigest)
{
	return interface_sendSystemMsgToUser(m_groupReqIndex++, sendUsers, msgDataType, msgStr, msgDigest);
}

int StarRtcCore::sendSystemGroupMsg(char* groupId, int msgDataType, char* msgStr, char* msgDigest)
{
	return interface_sendSystemGroupMsg(m_groupReqIndex++, groupId, msgDataType, msgStr, msgDigest);
}

int StarRtcCore::applySetGroupPushIgnore(char* groupId)
{
	return interface_applySetGroupPushIgnore(groupId);
}

int StarRtcCore::applyUnsetGroupPushIgnore(char* groupId)
{
	return interface_applyUnsetGroupPushIgnore(groupId);
}

int StarRtcCore::setPushMode(char* pushMode)
{
	return interface_applyUnsetGroupPushIgnore(pushMode);
}

int StarRtcCore::getPushMode()
{
	return interface_getPushMode();
}

/*
* 创建ChatRoom
*/
bool StarRtcCore::createChatRoom(string serverIp, int serverPort, string strName, int chatroomType)
{
	char name[128] = { 0 };
	strcpy(name, strName.c_str());
	printf("--------------createChatRoom start-----------\n");
	int ret = interface_createChatRoom((char*)serverIp.c_str(), serverPort, (char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), (char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(), (char*)m_pUserManager->m_strTokenId.c_str(), chatroomType, 100, name);
	printf("------------------createChatRoom end ret:%d-------\n", ret);
	return true;
}

/*
* 加入ChatRoom
*/
bool StarRtcCore::joinChatRoom(string serverIp, int serverPort, string strChatroomId)
{
	bool bRet = true;
	printf("--------------joinChatRoom start-----------\n");
	int ret = interface_joinChatRoom((char*)serverIp.c_str(), serverPort, (char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), (char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(), (char*)m_pUserManager->m_strTokenId.c_str(), (char*)strChatroomId.c_str());
	printf("------------------joinChatRoom end ret:%d-------\n", ret);
	if (ret != 0)
	{
		bRet = false;
	}
	return bRet;
}

/*
* 查询chatroom在线人数
*/
bool StarRtcCore::getOnlineNumber(string strChatroomId)
{
	bool bRet = true;
	printf("--------------getOnlineNumber start-----------\n");
	interface_queryRoomOnlineNumber((char*)strChatroomId.c_str());
	printf("------------------getOnlineNumber end-------\n");
	return bRet;
}

bool StarRtcCore::banToSendMsg(char* banUserId, int banTime)
{
	bool bRet = true;
	printf("--------------banToSendMsg start-----------\n");
	int ret = interface_banToSendMsg(banUserId, banTime);
	printf("------------------banToSendMsg end ret:%d-------\n", ret);
	if (ret != 0)
	{
		bRet = false;
	}
	return bRet;
}

bool StarRtcCore::kickOutUser(char* kickOutUserId)
{
	bool bRet = true;
	printf("--------------kickOutUser start-----------\n");
	int ret = interface_kickOutUser(kickOutUserId);
	printf("------------------kickOutUser end ret:%d-------\n", ret);
	if (ret != 0)
	{
		bRet = false;
	}
	return bRet;
}

bool StarRtcCore::sendChat(CIMMessage* pIMMessage)
{
	string strMsg = CMsgUtil::toJson(pIMMessage);
	bool bRet = true;
	printf("--------------sendChat start-----------\n");
	int ret = interface_sendChat((char*)strMsg.c_str());
	printf("------------------sendChat end ret:%d-------\n", ret);
	if (ret != 0)
	{
		bRet = false;
	}
	return bRet;
}

bool StarRtcCore::sendPrivateChat(char* toUserId, char* msgData)
{
	bool bRet = true;
	printf("--------------sendPrivateChat start-----------\n");
	int ret = interface_sendPrivateChat(toUserId, msgData);
	printf("------------------sendPrivateChat end ret:%d-------\n", ret);
	if (ret != 0)
	{
		bRet = false;
	}
	return bRet;
}

bool StarRtcCore::deleteChatRoom()
{
	bool bRet = true;
	printf("--------------deleteChatRoom start-----------\n");
	int ret = interface_deleteChatRoom();
	printf("------------------deleteChatRoom end ret:%d-------\n", ret);
	if (ret != 0)
	{
		bRet = false;
	}
	return bRet;
}

/*
*  与ChatRoom断开连接
*/
bool StarRtcCore::stopChatRoomConnect()
{
	printf("--------------stopChatRoomConnect start-----------\n");
	interface_stopChatRoomConnection();
	printf("------------------stopChatRoomConnect end-------\n");
	return true;
}


/*
* Channel 申请下载
*/
bool StarRtcCore::applyDownload(string serverIp, int port, string channelId)
{
	bool bret = true;
	printf("--------------startApplyDownload start-----------\n");
	int ret = interface_starLiveApplyDownload((char*)serverIp.c_str(), port, (char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), (char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(), (char*)m_pUserManager->m_strTokenId.c_str(), (char*)channelId.c_str());
	printf("--------------startApplyDownload end-----------\n");
	if (ret != 0)
	{
		bret = false;
	}
	return bret;
}

/*
* Channel 停止下载
*/
bool StarRtcCore::stopDownload()
{
	printf("--------------stopLiveDownload start-----------\n");
	interface_stopLiveDownload();
	printf("--------------stopLiveDownload end-----------\n");
	return true;
}
/*
* 设置数据流配置
*/
bool StarRtcCore::setStreamConfig(int* sendBuf, int length)
{
	printf("--------------setStreamConfig start-----------\n");
	byte_t buf[7] = { 0 };
	if (buf != NULL)
	{
		for (int i = 0; i < 7; i++)
		{
			buf[i] = sendBuf[i];
		}
		int ret = interface_setVdnDownloadStreamConfig(buf, length);

	}
	printf("--------------setStreamConfig end-----------\n");
	return true;
}

void StarRtcCore::setGlobalSetting(int videoEnable, int audioEnable,
	int videoBigIsHw,
	int videoBigWidth, int videoBigHeight, int videoBigFps, int videoBigBitrate,
	int videoSmallWidth, int videoSmallHeight, int videoSmallFps, int videoSmallBitrate,
	int openGLESEnable, int dynamicBitrateAndFpsEnable, int voipP2PEnable)
{
	printf("--------------setGlobalSetting start-----------\n");
	interface_doGlobalSetting(videoEnable, audioEnable,
		videoBigIsHw,
		videoBigWidth, videoBigHeight, videoBigFps, videoBigBitrate,
		videoSmallWidth, videoSmallHeight, videoSmallFps, videoSmallBitrate,
		openGLESEnable, dynamicBitrateAndFpsEnable, voipP2PEnable);
	printf("--------------setGlobalSetting end-----------\n");
}
/*
* 创建Channel
*/
bool StarRtcCore::createPublicChannel(string strServerIp, int port, string strName, int channelType, string strChatroomId)
{
	bool bret = true;
	printf("--------------createChannel start-----------\n");
	int ret = interface_starLiveCreatePublicChannel((char*)strServerIp.c_str(), port, (char*)m_pUserManager->m_ServiceParam.m_strAgentId.c_str(), (char*)m_pUserManager->m_ServiceParam.m_strUserId.c_str(), (char*)m_pUserManager->m_strTokenId.c_str(), (char*)strChatroomId.c_str(), channelType, (char*)strName.c_str(), 5);
	printf("--------------createChannel end-----------\n");
	if (ret != 0)
	{
		bret = false;
	}
	return bret;
}

int StarRtcCore::startLiveSrcEncoder(int audioSampleRateInHz, int audioChannels, int audioBitRate, int rotation)
{
	printf("--------------startLiveSrcEncoder start-----------\n");
	int ret = interface_startLiveSrcEncoder(audioSampleRateInHz, audioChannels, audioBitRate, rotation);
	printf("--------------startLiveSrcEncoder end-----------\n");
	return ret;
}

int StarRtcCore::startUploadSrcServer(char* servAddr, int servPort, char* agentId, char* userId, char* starToken, char* channelId/* ,int maxAudioPacketNum,int maxVideoPacketNum */)
{
	printf("--------------startUploadSrcServer start-----------\n");
	int ret = interface_starLiveStartUploadSrcServer(servAddr, servPort, agentId, userId, starToken, channelId);
	printf("--------------startUploadSrcServer end-----------\n");
	return ret;
}

int StarRtcCore::stopUploadSrcServer()
{
	printf("--------------stopUploadSrcServer start-----------\n");
	interface_stopUploadSrcServer();
	printf("--------------stopUploadSrcServer end-----------\n");
	return 0;
}

int StarRtcCore::stopLiveSrcCodec()
{
	printf("--------------stopLiveSrcCodec start-----------\n");
	interface_stopCodec();
	printf("--------------stopLiveSrcCodec end-----------\n");
	return 0;
}
//=========================================================================
//===========================    Msg回调    ===========================
//=========================================================================
//msgServer错误,这个函数是新线程调用
int StarRtcCore::msgErr(char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	return 0;
}
//重试多次后仍不能连接到msgServer，或用户主动调用stop后回调
int StarRtcCore::stop(void* userData)
{
	return 0;
}
//msgServer处于在线状态
int StarRtcCore::online(int maxContentLen, void* userData)
{
	return 0;
}
//msgServer中断状态
int StarRtcCore::offline(void* userData)
{
	return 0;
}
//发送消息的群信息还未同步完成，等待5秒再试
int StarRtcCore::groupIsSyncing(char* groupId, void* userData)
{
	return 0;
}
//收到单聊消息发送成功反馈
int StarRtcCore::sendMsgFin(int msgIndex, char* toUserId, uint32_t time, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pc2cMsgListener != NULL)
	{
		pStarRtcCore->m_pc2cMsgListener->onSendMessageSuccess(msgIndex);
	}
	return 0;
}


//收到群私信消息发送成功反馈
//typedef int (*fun_msg_sendPrivateGroupMsgFin)(int privateGroupMsgIndex,char* groupId,char* toUserId,uint32_t time,void* userData);
//收到单聊消息
int StarRtcCore::getNewMsg(char* fromUserId, uint32_t time, char* msgData, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pc2cMsgListener != NULL)
	{
		CIMMessage* pMessage = new CIMMessage();
		CMsgUtil::getJson(pMessage, msgData);
		pStarRtcCore->m_pc2cMsgListener->onNewMessage(pMessage);
		delete pMessage;
		pMessage = NULL;
	}	
	return 0;
}
//收到群消息
int StarRtcCore::getNewGroupMsg(char* groupId, char* fromUserId, uint32_t time, char* msgData, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pGroupMsgListener != NULL)
	{
		CIMMessage* pMessage = new CIMMessage();
		CMsgUtil::getJson(pMessage, msgData);
		pStarRtcCore->m_pGroupMsgListener->onReceivedMessage(groupId, pMessage);
		delete pMessage;
		pMessage = NULL;
	}
	return 0;
}

//收到群推送消息
int StarRtcCore::getGroupSystemMsg(char* groupId, uint32_t time, char* msgData, void* userData)
{
	return 0;
}

//收到系统推送消息
int StarRtcCore::getSystemMsg(uint32_t time, char* msgData, void* userData)
{
	return 0;
}

//下面几个函数的status参数为返回状态字
//status常见字串:
//GEN_SUCCESS //成功
//AECERRID_AEC_AUTH_FAILED, //AEC鉴权失败
//AECERRID_AEC_URL_CONNECT_FAILED, //AEC url连接失败
//AECERRID_AEC_RESPONSE_JSON_PARSE_ERR, //AEC返回的json格式解析错误
//GROUPPUSH_ERRID_GROUPID_IS_SYNCING
//GROUPPUSH_ERRID_USERID_IS_NOT_IN_GROUP, //此用户不在指定的群内
//收到群消息发送成功反馈
int StarRtcCore::sendGroupMsgFin(char* status, int groupMsgIndex, char* groupId, uint32_t time, void* userData)
{
	return 0;
}
int StarRtcCore::applyCreateGroupFin(char* status, int reqIndex, char* groupId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pGroupMsgListener != NULL)
	{
		pStarRtcCore->m_pGroupMsgListener->onApplyCreateGroupFin(groupId);
	}
	return 0;
}
int StarRtcCore::applyDelGroupFin(char* status, int reqIndex, char* groupId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pGroupMsgListener != NULL)
	{
		pStarRtcCore->m_pGroupMsgListener->onApplyDelGroupFin(groupId);
	}
	return 0;
}
int StarRtcCore::applyAddUserToGroupFin(char* status, int reqIndex, char* groupId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pGroupMsgListener != NULL)
	{
		pStarRtcCore->m_pGroupMsgListener->onApplyAddUserToGroupFin(groupId);
	}
	return 0;
}
int StarRtcCore::applyRemoveUserFromGroupFin(char* status, int reqIndex, char* groupId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pGroupMsgListener != NULL)
	{
		pStarRtcCore->m_pGroupMsgListener->onApplyRemoveUserFromGroupFin(groupId);
	}
	return 0;
}
int StarRtcCore::sendSystemMsgToUserFin(char* status, int reqIndex, void* userData)
{
	return 0;
}
int StarRtcCore::sendSystemGroupMsgFin(char* status, int reqIndex, char* groupId, void* userData)
{
	return 0;
}
int StarRtcCore::setPushModeOK(void* userData)
{
	return 0;
}
int StarRtcCore::setPushModeFailed(void* userData)
{
	return 0;
}
int StarRtcCore::getPushMode(char* pushMode, void* userData)
{
	return 0;
}
int StarRtcCore::setPushIgnoreFin(char* status, char* groupId, void* userData)
{
	return 0;
}
int StarRtcCore::unsetPushIgnoreFin(char* status, char* groupId, void* userData)
{
	return 0;
}

//=========================================================================
//===========================    live chatroom回调    ===========================
//=========================================================================
int StarRtcCore::createChatroomOK(char* roomId, int maxContentLen, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomCreateOK(roomId, maxContentLen);
	}
	return 0;
}

int StarRtcCore::createChatroomFailed(void* userData, char* errString)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomCreateFailed(errString);
	}
	return 0;
}

int StarRtcCore::joinChatroomOK(char* roomId, int maxContentLen, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomJoinOK(roomId, maxContentLen);
	}
	return 0;
}

int StarRtcCore::joinChatroomFailed(char* roomId, char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomJoinFailed(roomId, errString);
	}
	return 0;
}

int StarRtcCore::chatroomError(char* errString, void* userData)
{

	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatRoomErr(errString);
	}
	return 0;
}

int StarRtcCore::chatroomStop(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomStopOK();
	}
	return 0;
}

int StarRtcCore::deleteChatroomOK(char* roomId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomDeleteOK(roomId);
	}
	return 0;
}
int StarRtcCore::deleteChatroomFailed(char* roomId, char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomDeleteFailed(roomId, errString);
	}
	return 0;
}

int StarRtcCore::chatroomBanToSendMsgOK(char* banUserId, int banTime, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomBanToSendMsgOK(banUserId, banTime);
	}
	return 0;
}
int StarRtcCore::chatroomBanToSendMsgFailed(char* banUserId, int banTime, char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomBanToSendMsgFailed(banUserId, banTime, errString);
	}
	return 0;
}

int StarRtcCore::chatroomKickOutOK(char* kickOutUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomKickOutOK(kickOutUserId);
	}
	return 0;
}
int StarRtcCore::chatroomKickOutFailed(char* kickOutUserId, char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomKickOutFailed(kickOutUserId, errString);
	}
	return 0;
}

//被禁言
int StarRtcCore::chatroomSendMsgBanned(unsigned int remainTimeSec, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomSendMsgBanned(remainTimeSec);
	}
	return 0;
}
//被踢出房间
int StarRtcCore::chatroomKickedOut(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomKickedOut();
	}
	return 0;
}
//收到消息
int StarRtcCore::chatroomGetNewMsg(char* fromUserId, char* msgData, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		CIMMessage* pMessage = new CIMMessage();
		CMsgUtil::getJson(pMessage, msgData);
		pStarRtcCore->m_pStarIMChatroomListener->chatroomGetNewMsg(pMessage);
		delete pMessage;
		pMessage = NULL;	
	}
	return 0;
}
//收到私信消息
int StarRtcCore::chatroomGetNewPrivateMsg(char* fromUserId, char* msgData, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		CIMMessage* pMessage = new CIMMessage();
		CMsgUtil::getJson(pMessage, msgData);
		pStarRtcCore->m_pStarIMChatroomListener->chatroomGetNewPrivateMsg(pMessage);
		delete pMessage;
		pMessage = NULL;
	}
	return 0;
}
//收到房间人数信息
int StarRtcCore::chatroomGetRoomOnlineNumber(char* roomId, int onlineNum, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->getRoomOnlineNumber(roomId, onlineNum);
	}
	return 0;
}
//消息发送失败，余额不足
int StarRtcCore::chatroomSendMsgNoFee(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pStarIMChatroomListener != NULL)
	{
		pStarRtcCore->m_pStarIMChatroomListener->chatroomSendMsgNoFee();
	}
	return 0;
}

//=========================================================================
//===========================    liveVdn回调    ===========================
//=========================================================================

int StarRtcCore::applyDownloadChannelOK(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->applyDownloadChannelOK();
	}
	
	return 0;
}
int StarRtcCore::applyDownloadChannelFailed(char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->applyDownloadChannelFailed(errString);
	}
	return 0;
}

int StarRtcCore::downloadChannelError(char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->downloadChannelError(errString);
	}
	return 0;
}

int StarRtcCore::downloadStopOK(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->downloadStopOK();
	}
	return 0;
}
int StarRtcCore::downloadChannelClosed(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->downloadChannelClosed();
	}
	return 0;
}
int StarRtcCore::downloadChannelLeave(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->downloadChannelLeave();
	}
	return 0;
}

int StarRtcCore::downloadNetworkUnnormal(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->downloadNetworkUnnormal();
	}
	return 0;
}
int StarRtcCore::queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->queryVDNChannelOnlineNumberFin(channelId, totalOnlineNum);
	}
	return 0;
}
int StarRtcCore::uploaderAdd(char* upUserId, int upId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->uploaderAdd(upUserId, upId);
	}
	return 0;
}
int StarRtcCore::uploaderRemove(char* upUserId, int upId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->uploaderRemove(upUserId, upId);
	}
	return 0;
}
int StarRtcCore::downloadStreamConfigOK(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->downloadStreamConfigOK(channelId);
	}
	return 0;
}
int StarRtcCore::downloadStreamConfigFailed(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->downloadStreamConfigFailed();
	}
	return 0;
}
int StarRtcCore::getRealtimeData(int upId, uint8_t* data, int len, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->getRealtimeData(upId, data, len);
	}
	return 0;
}

//=========================================================================
//===========================    liveSrc回调    ===========================
//=========================================================================
int StarRtcCore::createChannelOK(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->createChannelOK(channelId);
	}
	return 0;
}
int StarRtcCore::createChannelFailed(char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->createChannelFailed(errString);
	}
	return 0;
}

int StarRtcCore::applyUploadChannelOK(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->applyUploadChannelOK(channelId);
	}
	return 0;
}
int StarRtcCore::applyUploadChannelFailed(char* errString, char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->applyUploadChannelFailed(errString, channelId);
	}
	return 0;
}

int StarRtcCore::setUploaderOK(char* channelId, char* uploadUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->setUploaderOK(channelId, uploadUserId);
	}
	return 0;
}
int StarRtcCore::setUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->setUploaderFailed(errString, channelId, uploadUserId);
	}
	return 0;
}

int StarRtcCore::unsetUploaderOK(char* channelId, char* uploadUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->unsetUploaderOK(channelId, uploadUserId);
	}
	return 0;
}
int StarRtcCore::unsetUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->unsetUploaderFailed(errString, channelId, uploadUserId);
	}
	return 0;
}

int StarRtcCore::muteUploaderOK(char* channelId, char* uploadUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->unsetUploaderOK(channelId, uploadUserId);
	}
	return 0;
}
int StarRtcCore::muteUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->unsetUploaderFailed(errString, channelId, uploadUserId);
	}
	return 0;
}

int StarRtcCore::unmuteUploaderOK(char* channelId, char* uploadUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->unsetUploaderOK(channelId, uploadUserId);
	}
	return 0;
}
int StarRtcCore::unmuteUploaderFailed(char* errString, char* channelId, char* uploadUserId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->unsetUploaderFailed(errString, channelId, uploadUserId);
	}
	return 0;
}

int StarRtcCore::deleteChannelOK(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->deleteChannelOK(channelId);
	}
	return 0;
}
int StarRtcCore::deleteChannelFailed(char* errString, char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->deleteChannelFailed(errString, channelId);
	}
	return 0;
}

int StarRtcCore::uploadUnseted(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->uploadUnseted(channelId);
	}
	return 0;
}
int StarRtcCore::uploadMuted(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->uploadMuted(channelId);
	}
	return 0;
}
int StarRtcCore::uploadUnmuted(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->uploadUnmuted(channelId);
	}
	return 0;
}

int StarRtcCore::setPeerStreamDownloadConfigOK(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->setPeerStreamDownloadConfigOK(channelId);
	}
	return 0;
}
int StarRtcCore::setPeerStreamDownloadConfigFailed(char* channelId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->setPeerStreamDownloadConfigFailed(channelId);
	}
	return 0;
}

int StarRtcCore::stopOK(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->stopOK();
	}
	return 0;
}
int StarRtcCore::isRetrying(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->isRetrying();
	}
	return 0;
}
int StarRtcCore::networkUnnormal(void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->networkUnnormal();
	}
	return 0;
}

int StarRtcCore::srcError(char* errString, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->srcError(errString);
	}
	return 0;
}
int StarRtcCore::querySrcChannelOnlineNumberFin(char* channelId, int totalOnlineNum, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->querySrcChannelOnlineNumberFin(channelId, totalOnlineNum);
	}
	return 0;
}

int StarRtcCore::uploaderAddSrc(char* upUserId, int upId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->uploaderAddSrc(upUserId, upId);
	}
	return 0;
}
int StarRtcCore::uploaderRemoveSrc(char* upUserId, int upId, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->uploaderRemoveSrc(upUserId, upId);
	}
	return 0;
}
int StarRtcCore::getRealtimeDataSrc(int upId, uint8_t* data, int len, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->getRealtimeDataSrc(upId, data, len);
	}
	return 0;
}

int StarRtcCore::getVideoRaw(int upId, int w, int h, uint8_t* videoData, int videoDataLen, void* userData)
{
	StarRtcCore* pStarRtcCore = (StarRtcCore*)userData;
	if (pStarRtcCore != NULL && pStarRtcCore->m_pVdnListener != NULL)
	{
		pStarRtcCore->m_pVdnListener->getVideoRaw(upId, w, h, videoData, videoDataLen);
	}

	if (pStarRtcCore != NULL && pStarRtcCore->m_pSrcListener != NULL)
	{
		pStarRtcCore->m_pSrcListener->getVideoRaw(upId, w, h, videoData, videoDataLen);
	}
	return 0;
}

