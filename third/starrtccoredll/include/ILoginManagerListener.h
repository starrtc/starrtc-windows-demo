#pragma once
class ILoginManagerListener
{
public:
	/**
	 * msgServer处于在线状态
	 */
	virtual int online(int maxContentLen) = 0;

	/**
	 * msgServer中断状态
	 */
	virtual int offline() = 0;
};
