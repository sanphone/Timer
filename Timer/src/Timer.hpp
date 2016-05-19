#pragma once

#include <thread>
#include <functional>
#include <iostream>

template<class T>
class CTimer
{
public:
	CTimer() {}
	CTimer(const int seconds, std::function<void(T)> f, T arg) :
		mTimerTime(seconds),
		timerFun(f),
		mTimerArgs(arg)
	{
	}
	~CTimer()
	{
	}

	void start()
	{
		mRunning = true;
		std::thread myThead(std::mem_fn(&CTimer::threadFun), this);
		myThead.detach();

	}

	void stop()
	{
		mRunning = false;
	}

	void setElapsed(std::function<void(T)> f, T arg)
	{
		timerFun = f;
		mTimerArgs = arg;
	}

	void setInterval(const int seconds)
	{
		mTimerTime = seconds;
	}

private:
	CTimer(const CTimer& timer) = delete;
	CTimer& operator=(CTimer& timer) = delete;
	void threadFun()
	{
		int counter = 0;
		while (mRunning && (counter < mTimerTime))
		{
			++counter;
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		if (mRunning == false)
		{
#if defined _DEBUG
			std::cout << "Timer had stoped" << std::endl;
#endif
			return;
		}

		timerFun(mTimerArgs);
	}

private:
	bool mRunning = false;
	int mTimerTime = 0;
	std::function<void(T)> timerFun;
	T mTimerArgs;
};