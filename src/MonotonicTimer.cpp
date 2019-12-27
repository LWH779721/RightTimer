#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "MonotonicTimer.h"

using namespace std;

namespace RightTimer {
	
MonotonicTimer::MonotonicTimer(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback):
	Timer(name, absOrRelative, delaySec, delayNsec, intervalSec, intervalNsec, callback){
}

bool MonotonicTimer::Init(){
	m_timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	if (m_timerfd < 0){
		perror("timerfd_create failed");
		return false;
	}
	
	return true;
}

bool MonotonicTimer::Start(){
	struct itimerspec new_value = {0};
	
	if (m_callback == nullptr){
		cout << "m_callback is nullptr" << endl;
		return false;	
	}
	
	new_value.it_value.tv_sec = m_delaySec;
	new_value.it_value.tv_nsec = m_delayNsec;
	new_value.it_interval.tv_sec = m_intervalSec;
	new_value.it_interval.tv_nsec = m_intervalNsec;
	
	if (timerfd_settime(m_timerfd, m_absOrRelative?TFD_TIMER_ABSTIME:0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
	
	return true;
}

bool MonotonicTimer::Reset(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback){
	struct itimerspec new_value = {0};
	
	m_absOrRelative = absOrRelative;
	m_delaySec = delaySec;
	m_delayNsec = delayNsec;
	m_intervalSec = intervalSec;
	m_intervalNsec = intervalNsec;
	m_callback = callback;
	
	new_value.it_value.tv_sec = m_delaySec;
	new_value.it_value.tv_nsec = m_delayNsec;
	new_value.it_interval.tv_sec = m_intervalSec;
	new_value.it_interval.tv_nsec = m_intervalNsec;
	
	if (timerfd_settime(m_timerfd, m_absOrRelative?TFD_TIMER_ABSTIME:0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
	
	return true;
}

bool MonotonicTimer::Stop(){
	struct itimerspec new_value = {0};
	
	if (timerfd_settime(m_timerfd, 0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
		
	return true;
}

MonotonicTimer::~MonotonicTimer(){
	if (m_timerfd){
		close(m_timerfd);
	}
}
}
