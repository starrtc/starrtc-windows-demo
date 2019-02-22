#pragma once
#include "StarRtcCore.h"
#include "IStarIMC2CListener.h"
#include <map>

class CChatManager : public IStarIMC2CListener
{
public:
	CChatManager(CUserManager* pUserManager, IStarIMC2CListener* pListener);
	virtual ~CChatManager();

	CIMMessage* sendMessage(char* toUserId, char* msgStr);

	bool sendOnlineMessage(char* toUserId, char* msgStr);

	virtual void onNewMessage(CIMMessage* var1);
	virtual void onSendMessageSuccess(int msgIndex);
	virtual void onSendMessageFailed(int msgIndex);

	void addMessageToMap(CIMMessage* pMsg);
	void removeMessageFromMap(int nIndex);
public:
	IStarIMC2CListener* m_pStarIMC2CListener;
	StarRtcCore* m_pStarRtcCore;
	map<string, CIMMessage*> m_MsgMap;
};

