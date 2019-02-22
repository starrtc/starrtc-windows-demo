#ifndef __START_LIVE_SRV__
#define __START_LIVE_SRV__
#include "stdafx.h"
#include <string>
using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif

class StartLiveSrc
{
public:
	/*
	 * 构造方法
	 */
	StartLiveSrc();
	/*
	 * 析构方法
	 */
	~StartLiveSrc();

	bool registerCallbackFunc();

	/*
	* 获取authKey
	*/
	bool getAuthKey(string userId);

	/*
	* 获取Token
	*/
	bool getToken(string userId, string agentId, string authKey);

	/*
	* 通过调度获取IM服务地址
	*/
	bool getIMServerAddr(string userId, string agentId);

	/*
	* 开启IM服务
	*/
	bool startIMServer(string strIP, int nPort, string userId, string agentId, string strToken);

	/*
	* 通过调度获取IM服务地址
	*/
	bool getIMServerAddr();

	/*
	* 登录
	*/
	bool logIn();

	/*
	* 通过调度获取ChatRoom服务地址
	*/
	bool getChatRoomServerAddr();

	/*
	* 创建ChatRoom
	*/
	bool createChatRoom();

	/*
	* 加入ChatRoom
	*/
	bool joinChatRoom();

	/*
	* 通过调度获取Channel服务地址
	*/
	bool getChannelServerAddr();

	/*
	* 创建Channel
	*/
	bool createChannel();

	/*
	* Channel 申请上传
	*/
	bool applyForUploading();

	/*
	* 上报chatroom 和 channelID
	*/
	bool reportChatRoomAndChannel();



	void setPPSData(unsigned char* videoData,int dataLen);
	void setSPSData(unsigned char* videoData,int dataLen);
	
	bool initDecode();
	
	//videoData的释放由此函数负责
	void insertVideo(unsigned char* videoData,int dataLen,int orderIndex);

	bool getServerInfo();
	
	bool getRomAddr();
	
	
	
	
	bool isStartSendData();
	bool isStartInit();
private:
	
	string  m_strUserId;
	string  m_strAgentId;
	string m_strAuthKey;
	string  m_strTokenId;


	string m_strIMServerIp;
	int m_nIMServerPort;

	string m_strChatRoomServerIp;
	int m_nChatRoomServerPort;

	string m_strChannelServerIp;
	int m_nChannelServerPort;


	unsigned char* m_PPSData;
	int m_PPSDataLen;
	unsigned char* m_SPSData;
	int m_SPSDataLen;
	
public:	
	
	
	bool m_bInitDecode;

	bool m_bCreateChatroomSuccess;
	bool m_bJoinChatroomSuccess;
	
	bool m_bCreateChannelSuccess;
	bool m_bApplyUpload;

	string m_ChatRoomId;
	string m_ChannelId;
};

#ifdef __cplusplus
}
#endif
#endif


