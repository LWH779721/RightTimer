#ifndef __REALTIMETIMER_HPP__
#define __REALTIMETIMER_HPP__

#include "Timer.h"

namespace RightTimer {

/**
 * Real Time Timer
 **/
class RealTimer:
	public Timer {
	friend class TimerDetector;
public:
	RealTimer(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	bool Init();
	
	bool Start();
	
	bool Stop();
	
	bool Reset(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	~RealTimer();
private:
	
};
};
	
#endif