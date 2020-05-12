#ifndef __MONOTONICTIMETIMER_HPP__
#define __MONOTONICTIMETIMER_HPP__

#include "Timer.h"

namespace RightTimer {

/**
 * Monotonic Time Timer
 **/
class MonotonicTimer: 
	public Timer,
    public std::enable_shared_from_this<MonotonicTimer>{
	friend class TimerDetector;
public:
	MonotonicTimer(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	bool Init() override;
    
    bool Init(std::shared_ptr<TimerDetector> timerDetector) override;
	
	bool Start() override;
	
	bool Stop() override;
	
	bool Reset(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback) override;

	bool Reset();
	
	~MonotonicTimer();
private:
};
};
	
#endif