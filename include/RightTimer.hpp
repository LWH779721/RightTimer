#ifndef __RIGHTTIMER_HPP__
#define __RIGHTTIMER_HPP__

#include <map>

using std::map;

namespace RightTimer {
	class Timer;
	typedef int (*timer_callback)(Timer &timer);
	
	class Timer {
		private:
			int tfd;
			bool repeat;
			bool abs;
			timer_callback cb;
			int SetUpAbsTimer(int delay);
			int SetUpRelativeTimer(int delay, int interval);
		public:
			Timer();
			int Init(bool abs, int delay, int interval, timer_callback cb);
			int RunCallback();
			int GetFd();
			bool GetRepeat();
			~Timer();
	};
	
	class TimerManage {
		private:
			static map<int, Timer *> timers;
			static int epfd;
			static int _Run();
		public:
			TimerManage();
			int Init();
			int Run();
			int AddTimer(bool abs, int delay, int interval, timer_callback cb);
			static int RemoveTimer(map<int, Timer *>::iterator it);
			static int Dump();
	};
};

#endif