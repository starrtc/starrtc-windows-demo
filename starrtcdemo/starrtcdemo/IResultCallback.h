#pragma once
#include <string>
using namespace std;
class IResultCallback
{
public:
	/**
	 * ³É¹¦
	 * @param data
	 */
	virtual void success() = 0;

	/**
	 * Ê§°Ü
	 * @param errMsg
	 */
	virtual void failed(string errMsg) = 0;
};

