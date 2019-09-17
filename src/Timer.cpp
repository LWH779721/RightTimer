#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "Timer.h"

using namespace std;

namespace RightTimer {
	
Timer::Timer():m_timerfd(-1){
	repeat = false;
	abs = false;
}

int Timer::SetUpAbsTimer(int delay){
	struct itimerspec new_value = {0};
	int timerfd;
	
	timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
	if (timerfd < 0){
		std::cout << "timerfd_create error" << std::endl;
		return -1;
	}

	new_value.it_value.tv_sec = delay;
	new_value.it_value.tv_nsec = 0;//delay%1000;
	
	if (timerfd_settime(timerfd, TFD_TIMER_ABSTIME, &new_value, NULL) != 0){
		std::cout << "timerfd_settime error" << std::endl;
		close(timerfd);
		return -1;
	}	
	
	return timerfd;
}

int Timer::SetUpRelativeTimer(int delay, int interval){
	struct itimerspec new_value = {0};
	int timerfd;
	
	timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	if (timerfd < 0){
		perror("timerfd_create failed");
		return -1;
	}

	if (delay == 0) delay = interval;
	
	new_value.it_value.tv_sec = delay/1000;
	new_value.it_value.tv_nsec = 0;
	
	if (interval){
		new_value.it_interval.tv_sec = interval/1000;
		new_value.it_interval.tv_nsec = interval%1000;
	}
	
	if (timerfd_settime(timerfd, 0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		close(timerfd);
		return -1;
	}	
		
	return timerfd;
}

int Timer::Init(bool abs, int delay, int interval, timer_callback cb, void *userdata){
	this->abs = abs;
	this->cb = cb;
	this->userdata = userdata;
	
	if (this->abs == true){
		m_timerfd = SetUpAbsTimer(delay);
	} else {
		m_timerfd = SetUpRelativeTimer(delay, interval);
	}
	
	if (interval > 0){
		this->repeat = true;
	}
	
	if (m_timerfd == -1){
		return -1;
	}
	
	return 0;
}

bool Timer::Pause(){
	struct itimerspec new_value = {0};
	
	if (timerfd_settime(m_timerfd, 0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
		
	return true;
}

int Timer::RunCallback()
{
	this->cb(this->userdata);
	return 0;
}

int Timer::GetFd()
{
	return m_timerfd;
}

bool Timer::GetRepeat()
{
	return repeat;
}

Timer::~Timer(){
	close(m_timerfd);
}
}
