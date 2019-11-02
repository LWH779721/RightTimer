#ifndef __MONOTONICTIMETIMER_HPP__
#define __MONOTONICTIMETIMER_HPP__

#include "Timer.h"

namespace RightTimer {

/**
 * Monotonic Time Timer
 **/
class MonotonicTimer: 
	public Timer {
	friend class TimerDetector;
public:
	MonotonicTimer(string name);
	
	bool Init();
	
	bool Start(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec);
	
	bool Stop();
	
	bool Restart();
	
	virtual void Run() = 0;
	
	~MonotonicTimer();
private:
};
};
	
#endif