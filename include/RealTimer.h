#ifndef __REALTIMETIMER_HPP__
#define __REALTIMETIMER_HPP__

#include "Timer.h"

namespace RightTimer {

/**
 * Real Time Timer
 **/
class RealTimer:
	public Timer,
    public std::enable_shared_from_this<RealTimer>{
	friend class TimerDetector;
public:
	RealTimer(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	bool Init() override;
	
    bool Init(std::shared_ptr<TimerDetector> timerDetector) override;
    
	bool Start() override;
	
	bool Stop() override;
	
	// auto restart
	bool Reset(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	bool Reset();
	
	~RealTimer();
private:
	
};
};
	
#endif