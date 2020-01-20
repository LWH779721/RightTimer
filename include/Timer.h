#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <string>
#include <functional>

using namespace std;

namespace RightTimer {

class Timer {
	friend class TimerDetector;
public:
	Timer(string name,
		bool absOrRelative = false, 
		unsigned int delaySec = 0, 
		unsigned int delayNsec = 0, 
		unsigned int intervalSec = 0, 
		unsigned int intervalNsec = 0,
		function<void()> callback = nullptr):
		m_timerfd(-1),
		m_absOrRelative(absOrRelative),
		m_execTimes(0),
		m_name(name),
		m_delaySec(delaySec),
		m_delayNsec(delayNsec),
		m_intervalSec(intervalSec),
		m_intervalNsec(intervalNsec),
		m_callback(callback){
	}
	
	virtual bool Init() = 0;
	
	// start Timer
	virtual bool Start() = 0;
	
	// stop Timer
	virtual bool Stop() = 0;
	
	// reset Timer
	virtual bool Reset(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback) = 0;
	virtual bool Reset() = 0;
	
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
	
	function<void()> m_callback;
};
}
	
#endif