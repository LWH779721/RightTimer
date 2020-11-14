#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "TimerDetector.h"
#include "Schedule.h"
#include "TimeUtil.h"

using namespace std;

namespace TimeWalker {
	
Schedule::Schedule(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback):
	TimeWalker(name, TimeType::REAL, absOrRelative, delaySec, delayNsec, intervalSec, intervalNsec, callback){
}

bool Schedule::Init(){
    if (!TimeWalker::Init()) {
        cout << "TimeWalker init failed" << endl;
        return false;
    }
	
    TimerDetector *tm = TimerDetector::GetDefaultDetector();
	tm->DetectTimer(shared_from_this());
	return true;
}

bool Schedule::Init(std::shared_ptr<TimerDetector> timerDetector){
    if (!TimeWalker::Init()) {
        cout << "TimeWalker init failed" << endl;
        return false;
    }
	
    timerDetector->DetectTimer(shared_from_this());
	return true;        
}

bool Schedule::at(const string& abstime){
    if (m_actived){
        stop();
	}
	
	m_absOrRelative = true;
	m_delaySec = abstime2ts(abstime);
	m_delayNsec = 0;
	m_intervalSec = 0;
	m_intervalNsec = 0;
	
	return start();        
}

bool Schedule::Start(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback){
    if (m_actived){
        stop();
	}
	
	m_absOrRelative = absOrRelative;
	m_delaySec = delaySec;
	m_delayNsec = delayNsec;
	m_intervalSec = intervalSec;
	m_intervalNsec = intervalNsec;
	m_callback = callback;
	
	return start();
}

Schedule::~Schedule(){

}
}
