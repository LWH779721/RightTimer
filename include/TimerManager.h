#ifndef __RIGHTTIMER_HPP__
#define __RIGHTTIMER_HPP__

#include <iostream>
#include <thread>
#include <map>

#include "Timer.h"

using namespace std;

namespace RightTimer {

class TimerManager {
public:
	static TimerManager *GetTimerManager();
	
	int NewTimer(bool abs, int delay, int interval, timer_callback cb, void *userdata);
	
	int RemoveTimer(std::map<int, Timer *>::iterator it);
	
	bool PauseTimer(int timerfd);
	
	int Dump();
private:	
	void ManageLoop();
	
	TimerManager();
	
	TimerManager(const TimerManager&);
	
	TimerManager& operator = (const TimerManager&);
	
	bool init();
		
	~TimerManager();	
private:
	static TimerManager *tm;
	
	std::map<int, Timer *> m_timers;
	
	int m_epfd;
	
	std::thread m_thread;
};

};

#endif