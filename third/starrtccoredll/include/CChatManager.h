#pragma once
#include "StarRtcCore.h"
#include "IChatManagerListener.h"
#include "IStarIMC2CListener.h"
#include "CUserManager.h"
#include <map>
/*
 *一对一聊天管理类
 */
class CChatManager : public IStarIMC2CListener
{
public:
	/*
	 * 构造函数
	 * @param pUserManager 用户信息
	 * @param pListener 回调函数指针
	 */
	CChatManager(CUserManager* pUserManager, IChatManagerListener* pListener);
	/*
	 * 析构函数
	 */
	virtual ~CChatManager();

	/*
	 * 发送消息
	 * @param toUserId 对方userId
	 * @param msgStr 消息内容
	 * @return 消息内容
	 */
	CIMMessage* sendMessage(char* toUserId, char* msgStr);

	/*
	 * 发送在线消息
	 * @param toUserId 对方userId
	 * @param msgStr 消息内容
	 * @return 是否成功
	 */
	bool sendOnlineMessage(char* toUserId, char* msgStr);

	/*
	 * 发送VOIP在线消息
	 * @param fromId 发送者userId
	 * @param targetId 对方userId
	 * @param code 消息类型
	 * @param data 消息内容
	 * @return 是否成功
	 */
	bool sendVoipOnlineMessage(char* fromId, char* targetId, int code, char* data);

	/*
	 * 接收到消息
	 * @param var1 消息类型
	 */
	virtual void onNewMessage(CIMMessage* var1);

	/*
	 * 发送消息成功回调
	 * @param msgIndex 消息序号
	 */
	virtual void onSendMessageSuccess(int msgIndex);

	/*
	 * 发送消息失败回调
	 * @param msgIndex 消息序号
	 */
	virtual void onSendMessageFailed(int msgIndex);

	/*
	 * 将消息存储到map
	 * @param pMsg 消息
	 */
	void addMessageToMap(CIMMessage* pMsg);

	/*
	 * 从map中移除消息
	 * @param nIndex 消息序号
	 */
	void removeMessageFromMap(int nIndex);
public:
	//用户信息
	CUserManager* m_pUserManager;
	//回调函数指针
	IChatManagerListener* m_pChatManagerListener;
	//接口类指针
	StarRtcCore* m_pStarRtcCore;
	//消息map
	map<string, CIMMessage*> m_MsgMap;
};

