#ifndef __TIMER_H__
#define __TIMER_H__

#include "TimeWalker.h"

namespace TimeWalker {

/**
 * Timer 使用计算机运行时间（Monotonic Time）实现，和现实时间无关
 **/
class Timer: 
	public TimeWalker{
	friend class TimerDetector;
public:
	Timer(string name);
	
	~Timer();
private:
};
};
	
#endif