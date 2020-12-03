#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "TimerDetector.h"
#include "Schedule.h"
#include "TimeUtil.h"

using namespace std;

namespace TimeWalker {
	
Schedule::Schedule(string name):
	TimeWalker(name, TimeType::REAL, TimeRelation::ABSOLUTE){
}

bool Schedule::at(const string& abstime){
    if (m_actived){
        stop();
	}
	
	m_delaySec = abstime2ts(abstime);
	m_delayNsec = 0;
	m_intervalSec = 0;
	m_intervalNsec = 0;
	
	return start();        
}

Schedule::~Schedule(){

}
}
