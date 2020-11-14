#ifndef __ALARM_HPP__
#define __ALARM_HPP__

#include "Schedule.h"
#include "TimerDetector.h"

using namespace TimeWalker;

class Alarm{
public:
	Alarm(string name);
	
	void Run();
	
	~Alarm();
	
private:
    std::shared_ptr<Schedule> m_schedule;
};
	
#endif