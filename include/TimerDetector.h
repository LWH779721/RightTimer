#ifndef __RIGHTTIMER_HPP__
#define __RIGHTTIMER_HPP__

#include <iostream>
#include <thread>
#include <map>

#include "Timer.h"

using namespace std;

namespace RightTimer {

class TimerDetector {
public:
	static TimerDetector *GetDefaultDetector();
	
	bool DetectTimer(Timer *t);
	
	int RemoveTimer(std::map<int, Timer *>::iterator it);
	
	bool PauseTimer(int timerfd);
	
	bool StopTimer(int timerfd);
	
	int Dump();
	
	~TimerDetector();	
private:	
	void ManageLoop();
	
	TimerDetector();
	
	TimerDetector(const TimerDetector&);
	
	TimerDetector& operator = (const TimerDetector&);
	
	bool init();
private:
	static TimerDetector *defaultDetector;
	
	std::map<int, Timer *> m_timers;
	
	int m_epfd;
	
	std::thread m_thread;
};

};

#endif