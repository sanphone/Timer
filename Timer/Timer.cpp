// Timer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "src/Timer.hpp"
#include <iostream>
#include <functional>

void fun(int arg)
{
	std::cout << "time function call:" << arg << std::endl;
}

void timerTest(CTimer<int>** timer)
{
	std::function<void(int)> timerFun = fun;
	if (*timer == nullptr)
	{
		*timer = new CTimer<int>(3, timerFun, 10);
	}
	else
	{
		(*timer)->stop();
	}
	
	(*timer)->start();
}


int main()
{
	CTimer<int>* timer = nullptr;
	timerTest(&timer);

	std::this_thread::sleep_for(std::chrono::seconds(5));

	if (timer != nullptr)
	{
		delete timer;
		timer = nullptr;
	}

	system("pause");
    return 0;
}

