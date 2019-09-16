#ifndef __TIMER_HPP__
#define __TIMER_HPP__

namespace RightTimer {

typedef int (*timer_callback)(void *userdata);

class Timer {
	friend class TimerManager;
public:
	Timer();
	int Init(bool abs, int delay, int interval, timer_callback cb, void *userdata);
	int RunCallback();
	int GetFd();
	bool GetRepeat();
	bool Pause();
	~Timer();
	
private:	
	int SetUpAbsTimer(int delay);
	int SetUpRelativeTimer(int delay, int interval);
	
private:
	int m_timerfd;
	bool repeat;
	bool abs;
	void *userdata;
	timer_callback cb;	
};
};
	
#endif