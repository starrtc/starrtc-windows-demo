#include "stdafx.h"
#include "StartLiveSrc.h"
#include<time.h>
#include<stdlib.h>


int fun_live_src_apply_upload_channel_ok2(char* channelId,void* userData)
{
	StartLiveSrc* pStartLiveSrc = (StartLiveSrc*)userData;
	pStartLiveSrc->m_bApplyUpload = true;
        printf("--------------------------------------------------------------applyForUploading success! channelId:%s\n", channelId);
        return 0;
}

int fun_live_src_apply_upload_channel_failed2(char* channelId,void* userData)
{
	StartLiveSrc* pStartLiveSrc = (StartLiveSrc*)userData;
	pStartLiveSrc->m_bApplyUpload = false;
        printf("-----------------------------------------------applyForUploading failed! channelId:%s\n", channelId);
        return 0;
}

int fun_live_src_create_channel_ok1(char* channelId,void* userData)
{
	StartLiveSrc* pStartLiveSrc = (StartLiveSrc*)userData;
	pStartLiveSrc->m_ChannelId = channelId;
	pStartLiveSrc->m_bCreateChannelSuccess = true;
        printf("-----------------------------------------------fun_live_src_create_channel_ok1 success! channelId:%s\n", channelId);
        return 0;
}

int fun_live_src_create_channel_failed1(char* channelId,void* userData)
{
	StartLiveSrc* pStartLiveSrc = (StartLiveSrc*)userData;

	pStartLiveSrc->m_bCreateChannelSuccess = false;
        printf("-----------------------------------------------fun_live_src_create_channel_failed1! channelId:%s\n", channelId);
        return 0;
}

int chatroom_create_ok(char* roomId,int maxContentLen,void* userData)
{
	StartLiveSrc* pStartLiveSrc = (StartLiveSrc*)userData;
	pStartLiveSrc->m_ChatRoomId = roomId;
	pStartLiveSrc->m_bCreateChatroomSuccess = true;
        printf("-----------------------------------------------chatroom_create_ok! roomId:%s\n", roomId);
        return 0;
}

int chatroom_create_failed(void* userData,char* errString)
{
	StartLiveSrc* pStartLiveSrc = (StartLiveSrc*)userData;
	pStartLiveSrc->m_bCreateChatroomSuccess = false;
        printf("-----------------------------------------------chatroom_create_failed! errString:%s\n", errString);
        return 0;
}

int chatroom_join_ok(char* roomId,int maxContentLen,void* userData)
{
	StartLiveSrc* pStartLiveSrc = (StartLiveSrc*)userData;
	pStartLiveSrc->m_bJoinChatroomSuccess = true;
        printf("-----------------------------------------------chatroom_join_ok! roomId:%s\n", roomId);
        return 0;
}

int chatroom_join_failed(char* roomId,char* errString,void* userData)
{
	StartLiveSrc* pStartLiveSrc = (StartLiveSrc*)userData;
	pStartLiveSrc->m_bJoinChatroomSuccess = false;
	printf("-----------------------------------------------chatroom_join_failed! errString:%s\n", errString);
	return 0;
}



StartLiveSrc::StartLiveSrc()
{
	m_strUserId = "";
	m_strAgentId = "";
	m_strAuthKey = "";
	m_strTokenId = "";

	m_strIMServerIp = "";
	m_nIMServerPort = 0;

	m_strChatRoomServerIp = "";
	m_nChatRoomServerPort = 0;

	m_strChannelServerIp = "";
	m_nChannelServerPort = 0;

	
	m_bInitDecode = false;
	
	m_bCreateChatroomSuccess = false;
	m_bJoinChatroomSuccess = false;

	m_bCreateChannelSuccess = false;
	m_bApplyUpload = false;

	
	
	m_ChatRoomId = "";
	m_ChannelId = "";
	
	m_PPSData = NULL;
	m_PPSDataLen = 0;
	m_SPSData = NULL;
	m_SPSDataLen = 0;
	m_strUserId = "";
	m_strAgentId = "";
	
	if(m_strUserId == "")
	{
		srand((int)time(0));
		int nUserId = rand()%1000000+1000000;
		char s[12];             //设定12位对于存储32位int值足够  
	
		sprintf(s, "%d", nUserId);
		m_strUserId = s;
	}
	
	//m_strChannelId = "kvJJAtjDpU5saaGa";

	
	m_strTokenId = "6Q7E2E5CQLWS56BDZLYV81661A78A26D";
	registerCallbackFunc();
}

StartLiveSrc::~StartLiveSrc()
{
	
}


bool StartLiveSrc::registerCallbackFunc()
{						  
	callbackInit_liveVideoSrc((fun_live_src_create_channel_ok)fun_live_src_create_channel_ok1,
								(fun_live_src_create_channel_failed)fun_live_src_create_channel_failed1,
								(fun_live_src_apply_upload_channel_ok)fun_live_src_apply_upload_channel_ok2,
								(fun_live_src_apply_upload_channel_failed)fun_live_src_apply_upload_channel_failed2,
								NULL,	// fun_live_src_set_uploader_ok
								NULL,	//fun_live_src_set_uploader_failed
								NULL,	//fun_live_src_unset_uploader_ok
								NULL,	//fun_live_src_unset_uploader_failed
								NULL,	//fun_live_src_mute_uploader_ok
								NULL,	//fun_live_src_mute_uploader_failed
								NULL,	//fun_live_src_unmute_uploader_ok
								NULL,	//fun_live_src_unmute_uploader_failed
								NULL,	//fun_live_src_delete_channel_ok
								NULL,	//fun_live_src_delete_channel_failed
								NULL,	//fun_live_src_upload_unseted
								NULL,	//fun_live_src_upload_muted
								NULL,	//fun_live_src_upload_unmuted
								NULL,	//fun_live_src_set_peer_stream_download_config_ok
								NULL,	//fun_live_src_set_peer_stream_download_config_failed
								NULL,	//fun_live_src_stop_ok
								NULL,	//fun_live_src_is_retrying
								NULL,	//fun_live_src_network_unnormal
								NULL,	//fun_live_src_error
								NULL,	//fun_live_query_src_channel_online_number_fin
								NULL,	//fun_live_src_uploader_add
								NULL,	//fun_live_src_uploader_remove
								NULL,	//fun_live_src_get_realtime_data
								this);
								
								
	callbackInit_chatRoom( chatroom_create_ok,
						   chatroom_join_ok,
						   chatroom_create_failed,
						   chatroom_join_failed,
						   NULL,//fun_chatroom_error chatroom_error,
						   NULL,//fun_chatroom_stop_ok chatroom_stop_ok,
						   NULL,//fun_chatroom_delete_ok chatroom_delete_ok,
						   NULL,//fun_chatroom_delete_failed chatroom_delete_failed,
						   NULL,//fun_chatroom_banToSendMsg_ok chatroom_banToSendMsg_ok,
						   NULL,//fun_chatroom_banToSendMsg_failed chatroom_banToSendMsg_failed,
						   NULL,//fun_chatroom_kickOut_ok chatroom_kickOut_ok,
						   NULL,//fun_chatroom_kickOut_failed chatroom_kickOut_failed,
						   NULL,//fun_chatroom_sendMsgBanned chatroom_sendMsgBanned,                  
						   NULL,//fun_chatroom_kickedOut chatroom_kickedOut,
						   NULL,//fun_chatroom_getNewMsg chatroom_getNewMsg,
						   NULL,//fun_chatroom_getNewPrivateMsg chatroom_getNewPrivateMsg,
						   NULL,//fun_chatroom_getRoomOnlineNumber chatroom_getRoomOnlineNumber,
						   NULL,//fun_chatroom_sendMsgNoFee chatroom_sendMsgNoFee,
						   this);	
	return true;	
}


/*
* 获取authKey
*/
bool StartLiveSrc::getAuthKey(string userId)
{
	bool bRet = false;
	m_strAuthKey = "";

	string url = "https://api.starrtc.com/demo/authKey?userid="+m_strUserId;
	int port = 9904;  
	char* data = "";
	std::string strVal = "";
	std::string strErrInfo = "";

	int ret = libcurl_post(url.c_str(), data, strVal, strErrInfo);
	printf("getAuthKey info:%s err:%s\n", strVal.c_str(), strErrInfo.c_str());

	cJSON* root = cJSON_Parse(strVal.c_str());     
    if (!root) 
    {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
    }
	cJSON *itemStatus = cJSON_GetObjectItem(root, "status");

	if(itemStatus == NULL)
	{
		printf("get status err: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
	}
	if(itemStatus->valueint != 1)
	{
		printf("status is 0  failed\n");
		return bRet;
	}
                
	cJSON *itemData = cJSON_GetObjectItem(root, "data");    
        
	printf("%s\n", itemData->valuestring);
	m_strAuthKey = itemData->valuestring;
	bRet = true;
	return bRet;
}

/*
* 获取Token
*/
bool StartLiveSrc::getToken(string userId, string agentId, string authKey)
{
	bool bRet = false;
	m_strTokenId = "";
	string url = "http://ips.starrtc.com:9920";
	int port = 9904;

	string strData = "userId="+agentId+"_"+userId+"&authKey="+authKey;
	std::string strVal = "";
	std::string strErrInfo = "";

	int ret = libcurl_post(url.c_str(), strData.c_str(), strVal, strErrInfo);
	printf("getToken info:%s err:%s %s\n", strVal.c_str(), strErrInfo.c_str(), agentId.c_str());

	cJSON* root = cJSON_Parse(strVal.c_str());     
    if (!root) 
    {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
    }
	cJSON *itemStatus = cJSON_GetObjectItem(root, "status");
	if(itemStatus == NULL)
	{
		printf("get status err: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
	}

	string str = itemStatus->valuestring;
	if(str != "1")
	{
		printf("status is 0  failed %s\n", str.c_str());
		return bRet;
	}
                
	cJSON *itemData = cJSON_GetObjectItem(root, "data");    
        
	printf("%s:", itemData->string);
	printf("%s\n", itemData->valuestring);
	m_strTokenId = itemData->valuestring;
	bRet = true;
	return bRet;
}

/*
* 通过调度获取IM服务地址
*/
bool StartLiveSrc::getIMServerAddr(string userId, string agentId)
{
	bool bRet = false;
	m_strIMServerIp = "";
	m_nIMServerPort = 0;

	string url = "http://ips.starrtc.com:9904";
	string strData = "userId="+agentId+"_"+userId;
	std::string strVal = "";
	std::string strErrInfo = "";

	int ret = libcurl_post(url.c_str(), strData.c_str(), strVal, strErrInfo);
	printf("getIMServerAddr info:%s err:%s\n", strVal.c_str(), strErrInfo.c_str());

	cJSON* root = cJSON_Parse(strVal.c_str());     
    if (!root) 
    {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
    }
	cJSON *itemStatus = cJSON_GetObjectItem(root, "status");
	
	if(itemStatus == NULL)
	{
		printf("get status err: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
	}
	string str = itemStatus->valuestring;
	if(str != "1")
	{
		printf("status is 0  failed %s\n", str.c_str());
		return bRet;
	}
                
	cJSON *itemData = cJSON_GetObjectItem(root, "data");    
        
	printf("%s\n", itemData->valuestring);
	str = itemData->valuestring;
	int pos = str.find(":");

	m_strIMServerIp = str.substr(0,pos);
	str = str.substr(pos+1,str.length());
	m_nIMServerPort = atoi(str.c_str());
	printf("m_strIMServerIp:%s m_nIMServerPort:%d \n",m_strIMServerIp.c_str(),m_nIMServerPort);
	bRet = true;
	return bRet;
}

/*
* 开启IM服务
*/
bool StartLiveSrc::startIMServer(string strIP, int nPort, string userId, string agentId, string strToken)
{
	printf("--------------logIn start-----------\n");
	int ret = interface_msgServerStart((char*)strIP.c_str(),nPort,(char*)agentId.c_str(),(char*)userId.c_str(),(char*)strToken.c_str());
	printf("------------------login end ret:%d-------\n",ret);
	return true;
}
bool StartLiveSrc::logIn()
{
	bool bRet = getAuthKey(m_strUserId);
	if(bRet == false)
	{
		return bRet;
	}
	bRet = getToken(m_strUserId, m_strAgentId, m_strAuthKey);
	if(bRet == false)
	{
		return bRet;
	}
	bRet = getIMServerAddr(m_strUserId, m_strAgentId);
	if(bRet == false)
	{
		return bRet;
	}
	bRet = startIMServer((char*)m_strIMServerIp.c_str(), m_nIMServerPort, (char*)m_strUserId.c_str(), (char*)m_strAgentId.c_str(), (char*)m_strTokenId.c_str());
	
	return bRet;
}

/*
* 通过调度获取ChatRoom服务地址
*/
bool StartLiveSrc::getChatRoomServerAddr()
{
	bool bRet = false;
	string userId = m_strUserId;
	string agentId = m_strAgentId;
	m_strChatRoomServerIp = "";
	m_nChatRoomServerPort = 0;

	string url = "http://ips.starrtc.com:9907";
	string strData = "userId="+agentId+"_"+userId;
	std::string strVal = "";
	std::string strErrInfo = "";

	int ret = libcurl_post(url.c_str(), strData.c_str(), strVal, strErrInfo);
	printf("getChatRoomServerAddr info:%s err:%s\n", strVal.c_str(), strErrInfo.c_str());

	cJSON* root = cJSON_Parse(strVal.c_str());     
    if (!root) 
    {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
    }
	cJSON *itemStatus = cJSON_GetObjectItem(root, "status");
	
	if(itemStatus == NULL)
	{
		printf("get status err: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
	}
	string str = itemStatus->valuestring;
	if(str != "1")
	{
		printf("status is 0  failed %s\n", str.c_str());
		return bRet;
	}
                
	cJSON *itemData = cJSON_GetObjectItem(root, "data");    
        
	printf("%s\n", itemData->valuestring);
	str = itemData->valuestring;
	int pos = str.find(":");

	m_strChatRoomServerIp = str.substr(0,pos);
	str = str.substr(pos+1,str.length());
	m_nChatRoomServerPort = atoi(str.c_str());
	printf("m_strChatRoomServerIp:%s m_nChatRoomServerPort:%d \n",m_strChatRoomServerIp.c_str(),m_nChatRoomServerPort);
	bRet = true;
	return bRet;
}

/*
* 创建并加入ChatRoom
*/
bool StartLiveSrc::createChatRoom()
{
	printf("--------------createChatRoom start-----------\n");
	int ret = interface_createChatRoom((char*)m_strChatRoomServerIp.c_str(), m_nChatRoomServerPort,(char*)m_strAgentId.c_str(), (char*)m_strUserId.c_str(), (char*)m_strTokenId.c_str(), 1, 100, "123456789"); 
	printf("------------------createChatRoom end ret:%d-------\n",ret);
}

/*
* 加入ChatRoom
*/
bool StartLiveSrc::joinChatRoom()
{
	printf("--------------joinChatRoom start-----------\n");
	int ret = interface_joinChatRoom((char*)m_strChatRoomServerIp.c_str(), m_nChatRoomServerPort,(char*)m_strAgentId.c_str(), (char*)m_strUserId.c_str(), (char*)m_strTokenId.c_str(), (char*)m_ChatRoomId.c_str()); 
	printf("------------------joinChatRoom end ret:%d-------\n",ret);
}

/*
* 通过调度获取Channel服务地址
*/
bool StartLiveSrc::getChannelServerAddr()
{
	string userId = m_strUserId;
	string agentId = m_strAgentId;
	bool bRet = false;
	m_strChannelServerIp = "";
	m_nChannelServerPort = 0;

	string url = "http://ips.starrtc.com:9929";
	string strData = "userId="+agentId+"_"+userId;
	std::string strVal = "";
	std::string strErrInfo = "";

	int ret = libcurl_post(url.c_str(), strData.c_str(), strVal, strErrInfo);
	printf("getChannelServerAddr info:%s err:%s\n", strVal.c_str(), strErrInfo.c_str());

	cJSON* root = cJSON_Parse(strVal.c_str());     
    if (!root) 
    {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
    }
	cJSON *itemStatus = cJSON_GetObjectItem(root, "status");
	
	if(itemStatus == NULL)
	{
		printf("get status err: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
	}
	string str = itemStatus->valuestring;
	if(str != "1")
	{
		printf("status is 0  failed %s\n", str.c_str());
		return bRet;
	}
                
	cJSON *itemData = cJSON_GetObjectItem(root, "data"); 
	if(itemData == NULL)
	{
		printf("get data err: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
	}

	cJSON *itemIP = cJSON_GetObjectItem(itemData, "ip"); 
	cJSON *itemPort = cJSON_GetObjectItem(itemData, "port"); 
	if(itemIP == NULL || itemPort == NULL)
	{
		printf("get ip or port err: [%s]\n",cJSON_GetErrorPtr());
		return bRet;
	}
   
        
	printf("%s\n", itemIP->valuestring);
	m_strChannelServerIp = itemIP->valuestring;
	m_nChannelServerPort = atoi(itemPort->valuestring);
	printf("m_strChannelServerIp:%s m_nChannelServerPort:%d \n",m_strChannelServerIp.c_str(),m_nChannelServerPort);
	bRet = true;
	return bRet;
}

/*
* 创建Channel
*/
bool StartLiveSrc::createChannel()
{
	printf("--------------createChannel start-----------ip:%s port:%d agentid:%s userid:%s tokenid:%s chatroomid:%s\n", m_strChannelServerIp.c_str(),m_nChannelServerPort, m_strAgentId.c_str(), (char*)m_strUserId.c_str(),(char*)m_strTokenId.c_str(), (char*)m_ChatRoomId.c_str());
	int ret = interface_starLiveCreatePublicChannel((char*)m_strChannelServerIp.c_str(), m_nChannelServerPort, (char*)m_strAgentId.c_str(), (char*)m_strUserId.c_str(), (char*)m_strTokenId.c_str(), (char*)m_ChatRoomId.c_str(),2,"123456789", 5);
	printf("------------------createChannel end ret:%d-------\n",ret);
	return true;
}

/*
* Channel 申请上传
*/
bool StartLiveSrc::applyForUploading()
{
	printf("--------------applyForUploading start-----------\n");
	interface_starLiveStartUploadSrcServer((char*)m_strChannelServerIp.c_str(), m_nChannelServerPort, (char*)m_strAgentId.c_str(), (char*)m_strUserId.c_str(), (char*)m_strTokenId.c_str(), (char*)m_ChannelId.c_str());
	printf("--------------applyForUploading end-----------\n");
}

/*
* 上报chatroom 和 channelID
*/
bool StartLiveSrc::reportChatRoomAndChannel()
{
	bool bRet = false;
	string strName = "armTest";
	string url = "http://api.starrtc.com/demo/live/store?ID="+m_ChannelId+m_ChatRoomId+"&Name="+strName+"&Creator="+m_strUserId;
	string strData = "";
	std::string strVal = "";
	std::string strErrInfo = "";

	int ret = libcurl_post(url.c_str(), strData.c_str(), strVal, strErrInfo);
	printf("reportChatRoomAndChannel info:%s err:%s\n", strVal.c_str(), strErrInfo.c_str());
	bRet = true;
	return bRet;
}

void StartLiveSrc::setPPSData(unsigned char* videoData,int dataLen)
{
	printf("--------------setPPSData start-----------\n");
	if(m_PPSData != NULL)
	{
		delete[] m_PPSData;
		m_PPSData = NULL;
	}
	m_PPSData = new unsigned char[dataLen];
	m_PPSDataLen = dataLen;
	memcpy(m_PPSData, videoData, sizeof(unsigned char)*dataLen);
	printf("--------------setPPSData end-----------\n");
}

void StartLiveSrc::setSPSData(unsigned char* videoData,int dataLen)
{
	printf("--------------setSPSData start-----------\n");
	if(m_SPSData != NULL)
	{
		delete[] m_SPSData;
		m_SPSData = NULL;
	}
	m_SPSData = new unsigned char[dataLen];
	m_SPSDataLen = dataLen;
	memcpy(m_SPSData, videoData, sizeof(unsigned char)*dataLen);
	printf("--------------setSPSData end-----------\n");
}
	
bool StartLiveSrc::initDecode()
{
	if(m_bInitDecode == false && m_SPSData != NULL && m_PPSData != NULL)
	{
		printf("--------------interface_startLiveSrcEncoder start----------- %d, %d, %s %s\n",m_SPSDataLen,m_PPSDataLen, m_SPSData, m_PPSData);
		int ret = interface_startLiveSrcEncoder(STAR_VIDEO_AND_AUDIO_CODEC_CONFIG_H264_AAC, 
																		  STAR_VIDEO_ENC_CONFIG_HW_720W_1280H_FPS15_RATE1200_GOP2, 
																		  STAR_VIDEO_ENC_CONFIG_NOT_USE, 
																		  16000, 
																		  1, 
																		  32, 
																		  m_SPSData, m_SPSDataLen,
																		  m_PPSData, m_PPSDataLen,
																		  NULL, 0,
																		  NULL, 0,
																		  0, 
																		  STAR_RTC_MEDIA_TYPE_VIDEO_ONLY);
		printf("--------------interface_startLiveSrcEncoder end ret:%d-----------\n", ret);
		if(ret >= 0)
		{
			m_bInitDecode = true;
		}
		else
		{
			printf("interface_startLiveSrcEncoder failed!\n");
		}
		
	}
	return m_bInitDecode;
}



void StartLiveSrc::insertVideo(unsigned char* videoData,int dataLen,int orderIndex)
{
	printf("--------------insertVideo start-----------\n");
	printf("liveId:%s%s,agentId:%s, userId:%s\n",m_ChannelId.c_str(),m_ChatRoomId.c_str(),m_strAgentId.c_str(), m_strUserId.c_str());
	unsigned char* temp = new unsigned char[dataLen];
	memcpy(temp, videoData, sizeof(unsigned char)*dataLen);
	interface_insertVideoNalu((byte_t*)temp,dataLen,STAR_VIDEO_ENC_CONFIG_SF_720W_1280H_FPS15_RATE1200_GOP2, orderIndex);
	printf("--------------insertVideo end-----------\n");
}

bool StartLiveSrc::isStartSendData()
{
	return m_bApplyUpload&&m_bInitDecode;
}

bool StartLiveSrc::isStartInit()
{
	bool bRet = false;
	if(m_bApplyUpload == true && m_bInitDecode == false && m_SPSData != NULL && m_PPSData != NULL)
	{
		bRet = true;
	}
	
	return bRet;
}
