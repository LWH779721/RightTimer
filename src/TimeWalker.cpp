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
        cout << "aleardy inited" << endl;
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

TimeWalker::~TimeWalker(){
	if (m_id){
		close(m_id);
	}
}
}
