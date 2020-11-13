#ifndef __ALARM_HPP__
#define __ALARM_HPP__

#include "MonotonicTimer.h"
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
	std::shared_ptr<MonotonicTimer> m_timer;
};
	
#endif