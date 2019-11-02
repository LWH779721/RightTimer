#ifndef __ALARM_HPP__
#define __ALARM_HPP__

#include "RealTimer.h"
#include "TimerDetector.h"
#include "TimerUtil.h"

using namespace RightTimer;

class Alarm:
	public RightTimer::RealTimer{
public:
	Alarm(string name);
	
	void Run();
	
	~Alarm();
	
private:
};
	
#endif