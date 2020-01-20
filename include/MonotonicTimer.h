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
	MonotonicTimer(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	bool Init();
	
	bool Start();
	
	bool Stop();
	
	bool Reset(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);

	bool Reset();
	
	~MonotonicTimer();
private:
};
};
	
#endif