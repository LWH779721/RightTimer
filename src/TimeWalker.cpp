#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "TimerDetector.h"
#include "TimeWalker.h"

using namespace std;

namespace TimeWalker {
	
TimeWalker::TimeWalker(string name,
    TimeType timeType,
	TimeRelation timeRelation):
    m_name(name),
    m_id(-1),
    m_timeType(timeType),
    m_timeRelation{timeRelation},
    m_inited(false),
    m_actived(false),
    m_execTimes(0),
	m_delaySec(0),
	m_delayNsec(0),
	m_intervalSec(0),
	m_intervalNsec(0),
	m_callback(nullptr){
}

void TimeWalker::setTarget(unsigned int sec, unsigned int nsec){
	m_delaySec = sec;
    m_delayNsec = nsec;	
}

void TimeWalker::setInterval(unsigned int sec, unsigned int nsec){
	m_intervalSec = sec;
    m_intervalNsec = nsec;	
} 	

void TimeWalker::setCallback(function<void()> callback){
	m_callback = callback;
}	

bool TimeWalker::init(){
    if (!__init()) {
        cout << "Time fd init failed" << endl;
        return false;
    }
	
    TimerDetector *tm = TimerDetector::GetDefaultDetector();
	tm->DetectTimer(shared_from_this());
	return true;
}

bool TimeWalker::init(std::shared_ptr<TimerDetector> timerDetector){
    if (!__init()) {
        cout << "Time fd init failed" << endl;
        return false;
    }
	
    timerDetector->DetectTimer(shared_from_this());
	return true;        
}

bool TimeWalker::__init(){
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
    
    if (!m_inited && !init()){
        cout << "Timer init failed" << endl;
		return false;
    }
    
	/*	处理timefd的问题，如果it_value为0则停止定时器，不管it_interval的值是否为0
	* 	Cause: Timer will stop when it_value is zero, No matter what the value of it_interval is
	*/
	if ((m_delaySec == 0)
		&& (m_delayNsec == 0)){
		new_value.it_value.tv_sec = m_intervalSec;
		new_value.it_value.tv_nsec = m_intervalNsec;
	} else {
		new_value.it_value.tv_sec = m_delaySec;
		new_value.it_value.tv_nsec = m_delayNsec;
	}
	
	new_value.it_interval.tv_sec = m_intervalSec;
	new_value.it_interval.tv_nsec = m_intervalNsec;
	
	if (timerfd_settime(m_id, (m_timeRelation == TimeRelation::ABSOLUTE)?TFD_TIMER_ABSTIME:0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
    
	m_actived = true;
	return true;
}

bool TimeWalker::stop(){
	if (!m_inited || !m_actived){
        cout << "already stoped" << endl;
        return false;
    }
    
    struct itimerspec new_value = {0};
	
	if (timerfd_settime(m_id, 0, &new_value, NULL) != 0){
		perror("timerfd_settime failed");
		return false;
	}	
	
	m_actived = false;	
	return true;
}

TimeWalker::~TimeWalker(){
	if (m_id){
		close(m_id);
	}
}
}
