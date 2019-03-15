#pragma once

#define MSG_SEND_TYPE_ON_LINE_NO_PUSH	0	//（用户不在线时,不推送、不入库）
#define MSG_SEND_TYPE_OFF_LINE_NO_PUSH	1	//（用户不在线时,不推送、入库）
#define MSG_SEND_TYPE_OFF_LINE_PUSH		2	//（用户不在线时,推送、入库）voipCalling
#define MSG_SEND_TYPE_ON_LINE_PUSH		3	//（用户不在线时,推送、不入库）

#define MSG_TYPE_CONTROL				0	//SDK内部 控制消息
#define MSG_TYPE_CUSTOMER				1	//用户自定义消息

//消息类型 = MSG_TYPE_CONTROL 时的业务码
   //voip信令（IM发送，不用送达反馈）
#define CONTROL_CODE_VOIP_CALL			1000//申请通话
#define CONTROL_CODE_VOIP_REFUSE		1001//拒绝通话
#define CONTROL_CODE_VOIP_HANGUP		1002//通话后挂断
#define CONTROL_CODE_VOIP_BUSY			1003//占线
#define CONTROL_CODE_VOIP_CONNECT		1004//接通

 //连麦互动信令（chatroom发送，需要送达反馈）
	//A是房主 B是观众
	//B主动申请连麦
#define CONTROL_CODE_LIVE_APPLY_LINK			2000 //B申请连麦
#define CONTROL_CODE_LIVE_APPLY_LINK_AGREE		2002 //A同意连麦
#define CONTROL_CODE_LIVE_APPLY_LINK_DISAGREE	2004 //A不同意连麦
//A邀请B连麦
#define CONTROL_CODE_LIVE_INVITE_LINK			2100 //A邀请连麦
#define CONTROL_CODE_LIVE_INVITE_LINK_AGREE		2102 //B同意连麦邀请
#define CONTROL_CODE_LIVE_INVITE_START_LINK		2104 //A准备就绪，请开始连麦
#define CONTROL_CODE_LIVE_INVITE_LINK_DISAGREE	2106 //B不同意连麦
//A让B停止连麦
#define CONTROL_CODE_LIVE_LINK_STOP				2200 //A停止连麦
