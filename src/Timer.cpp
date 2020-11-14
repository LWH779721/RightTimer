#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "TimerDetector.h"
#include "Timer.h"

using namespace std;

namespace TimeWalker {
	
Timer::Timer(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback):
	TimeWalker(name, TimeType::MONOTONIC, absOrRelative, delaySec, delayNsec, intervalSec, intervalNsec, callback){
}

bool Timer::Init(){
    if (!TimeWalker::Init()) {
        cout << "TimeWalker init failed" << endl;
        return false;
    }
	
    TimerDetector *tm = TimerDetector::GetDefaultDetector();
	tm->DetectTimer(shared_from_this());
	return true;
}

bool Timer::Init(std::shared_ptr<TimerDetector> timerDetector){
    if (!TimeWalker::Init()) {
        cout << "TimeWalker init failed" << endl;
        return false;
    }
	
    timerDetector->DetectTimer(shared_from_this());
	return true;        
}

bool Timer::Start(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback){	
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

Timer::~Timer(){

}
}
