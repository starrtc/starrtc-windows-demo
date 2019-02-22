#include "stdafx.h"
#include "CMsgUtil.h"
#include "json.h"
string CMsgUtil::toJson(CIMMessage* msg)
{
	string ret = "";
	if (msg == NULL )
	{
		return ret;
	}

	ret += "{\"fromId\":\"" + msg->m_strFromId + "\",";
	ret += "\"targetId\":\"" + msg->m_strTargetId + "\",";
	char buf[255] = { 0 };

	_i64toa_s(msg->m_Time, buf, sizeof(buf), 10);
	ret += "\"time\":";
	ret += buf;
	ret += ",";

	memset(buf, 0, sizeof(buf));
	_itoa_s(msg->m_nMsgIndex, buf, sizeof(buf), 10);
	ret += "\"msgIndex\":";
	ret += buf;
	ret += ",";

	memset(buf, 0, sizeof(buf));
	_itoa_s(msg->m_nType, buf, sizeof(buf), 10);
	ret += "\"type\":";
	ret += buf;
	ret += ",";

	memset(buf, 0, sizeof(buf));
	_itoa_s(msg->m_nCode, buf, sizeof(buf), 10);
	ret += "\"code\":";
	ret += buf;
	ret += ",";

	ret += "\"contentData\":\"" + msg->m_strContentData + "\"";

	if (msg->m_strAtList != "")
	{
		ret += ",\"atList\":\"" + msg->m_strAtList + "\"";
	}
	ret += "}";
	return ret;
}

void CMsgUtil::getJson(CIMMessage* msg, char* strData)
{
	if (msg == NULL || strData == NULL)
	{
		return;
	}
	string str_json = strData;
	Json::Reader reader;
	Json::Value root;
	if (str_json != "" && reader.parse(str_json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素   
	{
		if (root.isMember("fromId"))
		{
			msg->m_strFromId = root["fromId"].asCString();
		}

		if (root.isMember("targetId"))
		{
			msg->m_strTargetId = root["targetId"].asCString();
		}

		if (root.isMember("time"))
		{
			int nPos = str_json.find("time");
			if (nPos >= 0)
			{
				string str = str_json.substr(nPos + 6);
				nPos = str.find(",");
				if (nPos < 0)
				{
					nPos = str.length() - 2;
				}
				str = str.substr(0, nPos);
				msg->m_Time = atoll(str.c_str());
			}

			//	m_Time = root["time"].asUInt();
		}

		if (root.isMember("msgIndex"))
		{
			msg->m_nMsgIndex = root["msgIndex"].asInt();
		}

		if (root.isMember("type"))
		{
			msg->m_nType = root["type"].asInt();
		}

		if (root.isMember("code"))
		{
			msg->m_nCode = root["code"].asInt();
		}

		if (root.isMember("contentData"))
		{
			msg->m_strContentData = root["contentData"].asCString();
		}

		if (root.isMember("atList"))
		{
			msg->m_strAtList = root["atList"].asCString();
		}
	}
}

