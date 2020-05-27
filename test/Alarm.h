#ifndef __ALARM_HPP__
#define __ALARM_HPP__

#include "RealTimer.h"
#include "TimerDetector.h"

using namespace RightTimer;

class Alarm{
public:
	Alarm(string name);
	
	void Run();
	
	~Alarm();
	
private:
    std::shared_ptr<RealTimer> m_timer;
};
	
#endif