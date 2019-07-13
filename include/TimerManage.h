#ifndef __RIGHTTIMER_HPP__
#define __RIGHTTIMER_HPP__

#include <map>
#include "Timer.h"

namespace RightTimer {

	class TimerManage {
		private:
			std::map<int, Timer *> timers;
			int epfd;
			
			void ManageLoop();
			
			static TimerManage *tm;
			
			TimerManage();
			
			TimerManage(const TimerManage&);
			
			TimerManage& operator = (const TimerManage&);
		public:
			static TimerManage *GetTimerManager();

			int Start();
			int AddTimer(bool abs, int delay, int interval, timer_callback cb, void *userdata);
			int RemoveTimer(std::map<int, Timer *>::iterator it);
			int Dump();
	};
};

#endif