#pragma once

#define MSG_SEND_TYPE_ON_LINE_NO_PUSH	0	//（用户不在线时,不推送、不入库）
#define MSG_SEND_TYPE_OFF_LINE_NO_PUSH	1	//（用户不在线时,不推送、入库）
#define MSG_SEND_TYPE_OFF_LINE_PUSH		2	//（用户不在线时,推送、入库）voipCalling
#define MSG_SEND_TYPE_ON_LINE_PUSH		3	//（用户不在线时,推送、不入库）

#define MSG_TYPE_CONTROL				0	//SDK内部 控制消息
#define MSG_TYPE_CUSTOMER				1	//用户自定义消息
