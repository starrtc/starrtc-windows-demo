#pragma once
#include <string>
using namespace std;

enum ResultCallbackType
{
	RESULT_CALLBACK_VOIP_CALL,
	RESULT_CALLBACK_VOIP_CANCLE,
	RESULT_CALLBACK_VOIP_ACCEPT,
	RESULT_CALLBACK_VOIP_REFUSE,
	RESULT_CALLBACK_VOIP_HANGUP
};
class IResultCallback
{
public:
	/**
	 * ³É¹¦
	 * @param data
	 */
	virtual void success(ResultCallbackType type) = 0;

	/**
	 * Ê§°Ü
	 * @param errMsg
	 */
	virtual void failed(ResultCallbackType type, string errMsg) = 0;
};

