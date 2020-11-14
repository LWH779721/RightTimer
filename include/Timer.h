#ifndef __TIMER_H__
#define __TIMER_H__

#include "TimeWalker.h"

namespace TimeWalker {

/**
 * Timer 使用计算机运行时间（Monotonic Time）实现，和现实时间无关
 **/
class Timer: 
	public TimeWalker,
    public std::enable_shared_from_this<Timer>{
	friend class TimerDetector;
public:
	Timer(string name, bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	bool Init() override;
    
    bool Init(std::shared_ptr<TimerDetector> timerDetector) override;
	
    bool Start(bool absOrRelative, unsigned int delaySec, unsigned int delayNsec, unsigned int intervalSec, unsigned int intervalNsec, function<void()> callback);
	
	~Timer();
private:
};
};
	
#endif