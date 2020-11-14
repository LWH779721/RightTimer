#ifndef __ALARM_HPP__
#define __ALARM_HPP__

#include "Timer.h"
#include "TimerDetector.h"
#include "TimeUtil.h"

using namespace TimeWalker;

class WifiConnect{
public:
	WifiConnect(string name);
	
	void Run();
	
	void Run1();
	
	~WifiConnect();
	
private:
	std::shared_ptr<Timer> m_timer;
};
	
#endif