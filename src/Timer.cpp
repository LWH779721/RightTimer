#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "Timer.hpp"

using namespace RightTimer;
using namespace std;

Timer::Timer()
{
	tfd = 0;
	repeat = false;
	abs = false;
}

int Timer::SetUpAbsTimer(int delay)
{
	struct itimerspec new_value = {0};
	int timerfd;
	
	timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
	if (timerfd < 0)
	{
		std::cout << "timerfd_create error" << std::endl;
		return -1;
	}

	new_value.it_value.tv_sec = delay;
	new_value.it_value.tv_nsec = 0;//delay%1000;
	
	if (timerfd_settime(timerfd, TFD_TIMER_ABSTIME, &new_value, NULL) != 0)
	{
		std::cout << "timerfd_settime error" << std::endl;
		close(timerfd);
		return -1;
	}	
	
	return timerfd;
}

int Timer::SetUpRelativeTimer(int delay, int interval)
{
	struct itimerspec new_value = {0};
	int timerfd;
	
	timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	if (timerfd < 0)
	{
		std::cout << "timerfd_create error" << std::endl;
		return -1;
	}
	
	if (delay == 0) delay = interval;
	
	new_value.it_value.tv_sec = delay/1000;
	new_value.it_value.tv_nsec = delay%1000;
	new_value.it_interval.tv_sec = interval/1000;
	new_value.it_interval.tv_nsec = interval%1000;
	
	if (timerfd_settime(tfd, 0, &new_value, NULL) != 0)
	{
		std::cout << "timerfd_settime error" << std::endl;
		close(timerfd);
		return -1;
	}	
		
	return timerfd;
}

int Timer::Init(bool abs, int delay, int interval, timer_callback cb)
{
	this->abs = abs;
	this->cb = cb;
	
	if (this->abs == true)
	{
		tfd = SetUpAbsTimer(delay);
		this->repeat = false;
	}
	else
	{
		tfd = SetUpRelativeTimer(delay, interval);
		this->repeat = true;
	}
	
	if (tfd == -1)
	{
		return -1;
	}
	
	return 0;
}

int Timer::RunCallback()
{
	this->cb(*this);
	return 0;
}

int Timer::GetFd()
{
	return tfd;
}

bool Timer::GetRepeat()
{
	return repeat;
}

Timer::~Timer()
{
	close(tfd);
}
 