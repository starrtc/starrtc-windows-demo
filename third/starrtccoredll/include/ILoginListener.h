#pragma once
class ILoginListener
{
public:
	/**
	 * msgServer错误,这个函数是新线程调用
	 */
	virtual int msgErr(char* errString) = 0;

	/**
	 * 重试多次后仍不能连接到msgServer，或用户主动调用stop后回调
	 */
	virtual int stop() = 0;

	/**
	 * msgServer处于在线状态
	 */
	virtual int online(int maxContentLen) = 0;

	/**
	 * msgServer中断状态
	 */
	virtual int offline() = 0;
};
