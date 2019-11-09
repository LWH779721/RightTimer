#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <string>

using namespace std;

namespace RightTimer {

class Timer {
	friend class TimerDetector;
public:
	Timer(string name):
		m_timerfd(-1),
		m_absOrRelative(false),
		m_execTimes(0),
		m_name(name),
		m_delaySec(0),
		m_delayNsec(0),
		m_intervalSec(0),
		m_intervalNsec(0){
	}
	
	virtual bool Init(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec) = 0;
	
	// start Timer
	virtual bool Start() = 0;
	virtual bool Start(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec) = 0;
	
	// stop Timer
	virtual bool Stop() = 0;
	
	virtual void Run() = 0;	
protected:
	int m_timerfd;
	
	//abs Timer or relative Timer
	bool m_absOrRelative;
	
	// Timer exec times
	int m_execTimes;
	
	// Timer name for debug
	string m_name;
	
	unsigned int m_delaySec;
	
	unsigned int m_delayNsec;
	
	unsigned int m_intervalSec;
	
	unsigned int m_intervalNsec;
};
};
	
#endif