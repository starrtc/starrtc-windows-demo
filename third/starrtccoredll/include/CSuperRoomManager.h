#pragma once
#include "ISuperRoomManagerListener.h"
#include "CUserManager.h"
#include "CChatroomManager.h"
#include "ISrcManagerListener.h"
#include "IVdnManagerListener.h"
#include "CSrcManager.h"
#include "CVdnManager.h"
#include <map>
class CSuperRoomManager : public IChatroomManagerListener, public ISrcManagerListener, public IVdnManagerListener
{
public:
	CSuperRoomManager(CUserManager* pUserManager, ISuperRoomManagerListener* pListener);
	virtual ~CSuperRoomManager();
public:
	static void addChatroomGetListListener(IChatroomGetListListener* pChatroomGetListListener);
	static void getSuperRoomList(CUserManager* pUserManager, string strUserId, string listType);

	/**
	 * 设置媒体类型，音频和视频可以都打开，也可以单独打开一个。
	 * @param mediaTypeEnum
	 */
	void setRtcMediaType(int mediaTypeEnum);

	/**
	 * 创建直播
	 * @param superRoomItem XHSuperRoomItem 用于指定直播的名字和类型
	 */
	bool createSuperRoom(string strName, int chatroomType, int channelType);

	/**
	 * 加入超级聊天室
	 * @param roomID 直播ID
	 * @param callback 结果回调
	 */
	bool joinSuperRoom(string strChatRoomId, string strChannelId);

	/**
	 *  停止发言
	 *  @param callback 结果回调
	 */
	void layDownMic();

	/**
	 * 申请发言
	 * @param callback 结果回调
	 */
	bool pickUpMic();

	/**
	 * 离开聊天室
	 * @param callback 结果回调
	 */
	void leaveSuperRoom();

	/**
	* 命令连麦者下麦
	* @param toID 连麦者ID
	*/
	void commandToAudience(string toID);

	/**
	 * 切换成大图
	 * @param strUserID 切换成大图的用户ID
	 */
	bool changeToBig(string strUserID);

	/**
	 * 切换成小图
	 * @param userID 切换成小图的用户ID
	 */
	bool changeToSmall(string strUserID);

	/**
	* 动态开关音频，直播过程中可随时开关音频，直播结束后状态自动重置。
	*/
	void setAudioEnable(bool enable);

	/**
	 * 动态开关视频，直播过程中可随时开关视频，直播结束后状态自动重置。
	 */
	void setVideoEnable(bool enable);

	/**
	 * 发送会议消息
	 * @param message 发送的消息内容
	 * @param callback 结果回调
	 * @return 返回发送的消息对象
	 */
	CIMMessage* sendMessage(string strMessage);

	/**
	 * 发送会议私密消息
	 * 私密消息只有目标用户可以收到
	 * @param toID 目标用户ID
	 * @param message 发送的消息内容
	 * @return 返回发送的消息对象
	 */
	CIMMessage* sendPrivateMessage(string toID, string strMessage);

	/**
	 * 对会议中的某人禁言
	 * @param meetingID 会议ID
	 * @param memberID 被禁言者ID
	 * @param muteSeconds 禁言时间
	 * @param callback 结果回调
	 */
	bool muteMember(string strChatRoomId, string memberID, int muteSeconds);

	/**
	 * 解除会议中某人的禁言
	 * @param meetingID 会议ID
	 * @param memberID 被禁言者ID
	 */
	bool unMuteMember(string strChatRoomId, string memberID);

	/**
	 * 从会议室踢出用户
	 * @param meetingID 会议ID
	 * @param memberID 被踢者ID
	 */
	bool kickMember(string strChatRoomId, string memberID);

	/**
	 * 推送RTMP流
	 * @param rtmpurl 推送地址
	 */
	void pushRtmp(string rtmpurl);

	/**
	 * 停止推送RTMP流
	 */
	void stopPushRtmp();

	void insertAudioRaw(uint8_t* audioData, int dataLen);
	void insertVideoRaw(uint8_t* videoData, int dataLen, int isBig);
	int cropVideoRawNV12(int w, int h, uint8_t* videoData, int dataLen, int yuvProcessPlan, int rotation, int needMirror, uint8_t* outVideoDataBig, uint8_t* outVideoDataSmall);
	void querySoundData(uint8_t** pData, int* nLength);
	void insertRealtimeData(uint8_t* realtimeData, int dataLen);
	bool saveToList(string strRoomId, int listType, string data);
	/**
	 * 从列表删除
	 * @param userId 用户ID
	 * @param type 类型
	 * @param strChatroomId chatRoom ID
	 */
	void deleteFromList(string userId, int type, string strChatroomId);

	bool closeChatroom();

	bool closeLive();

	bool close();
public:
	/**
	 * 聊天室成员数变化
	 * @param number
	 */
	virtual void onMembersUpdated(int number);

	/**
	 * 自己被踢出聊天室
	 */
	virtual void onSelfKicked();

	/**
	 * 自己被禁言
	 */
	virtual void onSelfMuted(int seconds);

	/**
	 * 聊天室已关闭
	 */
	virtual void onClosed();

	/**
	 * 收到消息
	 * @param message
	 */
	virtual void onReceivedMessage(CIMMessage* pMessage);

	/**
	 * 收到私信消息
	 * @param message
	 */
	virtual void onReceivePrivateMessage(CIMMessage* pMessage);

public:
	//vdn
	virtual int uploaderAddVdn(char* upUserId, int upId);
	virtual int uploaderRemoveVdn(char* upUserId, int upId);
	virtual int getRealtimeDataVdn(int upId, uint8_t* data, int len);
	virtual int getVideoRawVdn(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	virtual int downloadChannelClosed();
	virtual int downloadChannelLeave();
	virtual int downloadNetworkUnnormal();
	virtual int queryVDNChannelOnlineNumberFin(char* channelId, int totalOnlineNum);

public:
	//src
	virtual int uploaderAddSrc(char* upUserId, int upId);
	virtual int uploaderRemoveSrc(char* upUserId, int upId);
	virtual int getRealtimeDataSrc(int upId, uint8_t* data, int len);
	virtual int getVideoRawSrc(int upId, int w, int h, uint8_t* videoData, int videoDataLen);

	virtual int deleteChannel(char* channelId);
	virtual int stopOK();
	virtual int srcError(char* errString);

public:
	ISuperRoomManagerListener* m_pListener;
	CUserManager* m_pUserManager;
	CChatroomManager* m_pChatroomManager;
	CSrcManager* m_pSrcManager;
	CVdnManager* m_pVdnManager;
	map<int, StarLiveUserInfo> m_StarLiveSrcUserInfo;
	map<int, StarLiveUserInfo> m_StarLiveVdnUserInfo;
};

