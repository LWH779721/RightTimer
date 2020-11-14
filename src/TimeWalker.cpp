#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "TimerDetector.h"
#include "TimeWalker.h"

using namespace std;

namespace TimeWalker {
	
TimeWalker::TimeWalker(string name,
    TimeType timeType,  
    bool absOrRelative,
    unsigned int delaySec, 
    unsigned int delayNsec, 
    unsigned int intervalSec, 
    unsigned int intervalNsec,
    function<void()> callback):
    m_name(name),
    m_id(-1),
    m_timeType(timeType),
    m_absOrRelative{absOrRelative},
    m_inited(false),
    m_actived(false),
    m_execTimes(0),
    m_delaySec(delaySec),
    m_delayNsec(delayNsec),
    m_intervalSec(intervalSec),
    m_intervalNsec(intervalNsec),
    m_callback(callback){
}

bool TimeWalker::Init(){
    if (m_inited) {
        cout << "already inited" << endl;
        return false;
    }
        
    if (m_timeType == TimeType::REAL){
        m_id = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
    } else {
        m_id = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
    }
    
	if (m_id < 0){
		perror("timerfd_create failed");
		return false;
	}
	
    m_inited = true;
	return true;
}

bool TimeWalker::start(){
	struct itimerspec new_value = {0};
	
	if (m_callback == nullptr){
		cout << "m_callback is nullptr" << endl;
		return false;	
	}
    
    if (!m_inited){
        cout << "Timer uninit" << endl;
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
	
	if (timerfd_settime(m_id, m_absOrRelative?TFD_TIMER_ABSTIME:0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
    
	m_actived = true;
	return true;
}

bool TimeWalker::stop(){
	if (!m_inited || !m_actived){
        cout << "already stoped" << endl;
        return true;
    }
    
    struct itimerspec new_value = {0};
	
	if (timerfd_settime(m_id, 0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
		
	return true;
}

TimeWalker::~TimeWalker(){
	if (m_id){
		close(m_id);
	}
}
}
