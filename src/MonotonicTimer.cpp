#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "TimerDetector.h"
#include "MonotonicTimer.h"

using namespace std;

namespace TimeWalker {
	
MonotonicTimer::MonotonicTimer(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback):
	Timer(name, absOrRelative, delaySec, delayNsec, intervalSec, intervalNsec, callback){
}

bool MonotonicTimer::Init(){
	m_timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	if (m_timerfd < 0){
		perror("timerfd_create failed");
		return false;
	}
	
    TimerDetector *tm = TimerDetector::GetDefaultDetector();
	tm->DetectTimer(shared_from_this());
    m_inited = true;
	return true;
}

bool MonotonicTimer::Init(std::shared_ptr<TimerDetector> timerDetector){
    m_timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	if (m_timerfd < 0){
		perror("timerfd_create failed");
		return false;
	}
	
    timerDetector->DetectTimer(shared_from_this());
    m_inited = true;
	return true;        
}

bool MonotonicTimer::Start(){
	struct itimerspec new_value = {0};
	
	if (m_callback == nullptr){
		cout << "m_callback is nullptr" << endl;
		return false;	
	}
    
    if (!m_inited && !Init()){
        cout << "Timer init failed" << endl;
		return false;
    }
    
	//Cause: Timer will stop when it_value is zero, No matter what the value of it_interval is
	if ((m_delaySec != 0)
		|| (m_delayNsec != 0)){
		new_value.it_value.tv_sec = m_delaySec;
		new_value.it_value.tv_nsec = m_delayNsec;
	} else {
		new_value.it_value.tv_sec = m_intervalSec;
		new_value.it_value.tv_nsec = m_intervalNsec;
	}
	
	new_value.it_interval.tv_sec = m_intervalSec;
	new_value.it_interval.tv_nsec = m_intervalNsec;
	
	if (timerfd_settime(m_timerfd, m_absOrRelative?TFD_TIMER_ABSTIME:0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
    
	m_actived = true;
	return true;
}

bool MonotonicTimer::Start(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback){	
	if (m_actived){
        Stop();
	}
    
	m_absOrRelative = absOrRelative;
	m_delaySec = delaySec;
	m_delayNsec = delayNsec;
	m_intervalSec = intervalSec;
	m_intervalNsec = intervalNsec;
	m_callback = callback;
	
	return Start();
}

bool MonotonicTimer::Stop(){
	if (!m_inited || !m_actived){
        return true;
    }
    
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
