#ifndef __ALARM_HPP__
#define __ALARM_HPP__

#include "MonotonicTimer.h"
#include "TimerDetector.h"
#include "TimerUtil.h"

using namespace RightTimer;

class WifiConnect{
public:
	WifiConnect(string name);
	
	void Run();
	
	void Run1();
	
	~WifiConnect();
	
private:
	MonotonicTimer *t;
};
	
#endif