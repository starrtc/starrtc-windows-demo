#pragma once
#include <string>
using namespace std;

class IErrorCallback
{
public:
	/**
	 * ±¨´í
	 * @param errMsg
	 * @param data
	 */
	virtual void error(string errMsg) = 0;
};

