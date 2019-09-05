#ifndef __RIGHTTIMER_HPP__
#define __RIGHTTIMER_HPP__

#include <iostream>
#include <thread>
#include <map>

#include "Timer.h"

namespace RightTimer {

class TimerManage {
private:
	static TimerManage *tm;
	
	std::map<int, Timer *> timers;
	
	int m_epfd;
	
	std::thread m_thread;
private:	
	void ManageLoop();
	
	TimerManage();
	
	TimerManage(const TimerManage&);
	
	TimerManage& operator = (const TimerManage&);
	
	bool init();
		
	~TimerManage();
public:
	static TimerManage *GetTimerManager();
	
	int NewTimer(bool abs, int delay, int interval, timer_callback cb, void *userdata);
	
	int RemoveTimer(std::map<int, Timer *>::iterator it);
	
	int Dump();
};

};

#endif