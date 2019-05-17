#include <iostream>
#include <thread>
#include <sys/timerfd.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>

#include "RightTimer.hpp"

using namespace RightTimer;
using namespace std;

map<int, Timer *> TimerManage::timers;
int TimerManage::epfd = 0;
			
Timer::Timer()
{
	tfd = 0;
	repeat = false;
	abs = false;
}

int Timer::SetUpAbsTimer(int delay)
{
	struct itimerspec new_value = {0};
	int timerfd;
	
	timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
	if (timerfd < 0)
	{
		std::cout << "timerfd_create error" << std::endl;
		return -1;
	}

	new_value.it_value.tv_sec = delay;
	new_value.it_value.tv_nsec = 0;//delay%1000;
	
	if (timerfd_settime(timerfd, TFD_TIMER_ABSTIME, &new_value, NULL) != 0)
	{
		std::cout << "timerfd_settime error" << std::endl;
		close(timerfd);
		return -1;
	}	
	
	return timerfd;
}

int Timer::SetUpRelativeTimer(int delay, int interval)
{
	struct itimerspec new_value = {0};
	int timerfd;
	
	timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	if (timerfd < 0)
	{
		std::cout << "timerfd_create error" << std::endl;
		return -1;
	}
	
	if (delay == 0) delay = interval;
	
	new_value.it_value.tv_sec = delay/1000;
	new_value.it_value.tv_nsec = delay%1000;
	new_value.it_interval.tv_sec = interval/1000;
	new_value.it_interval.tv_nsec = interval%1000;
	
	if (timerfd_settime(tfd, 0, &new_value, NULL) != 0)
	{
		std::cout << "timerfd_settime error" << std::endl;
		close(timerfd);
		return -1;
	}	
		
	return timerfd;
}

int Timer::Init(bool abs, int delay, int interval, timer_callback cb)
{
	this->abs = abs;
	this->cb = cb;
	
	if (this->abs == true)
	{
		tfd = SetUpAbsTimer(delay);
		this->repeat = false;
	}
	else
	{
		tfd = SetUpRelativeTimer(delay, interval);
		this->repeat = true;
	}
	
	if (tfd == -1)
	{
		return -1;
	}
	
	return 0;
}

int Timer::RunCallback()
{
	this->cb(*this);
	return 0;
}

int Timer::GetFd()
{
	return tfd;
}

bool Timer::GetRepeat()
{
	return repeat;
}

Timer::~Timer()
{
	close(tfd);
}
 
TimerManage::TimerManage()
{
	
}

int TimerManage::Init()
{
	epfd = epoll_create1(EPOLL_CLOEXEC);
    if (epfd == -1)
    {
        std::cout << "err when epoll create" << std::endl;
        return -1;
    }

	return epfd;
}

int TimerManage::AddTimer(bool abs, int delay, int interval, timer_callback cb)
{
	struct epoll_event ev;
	int ret = -1;
	Timer *t = new Timer;
	
	t->Init(abs, delay, interval, cb);
	std::cout << "AddTimer:" << t->GetFd() << std::endl;
	ev.data.fd = t->GetFd();
    ev.events = EPOLLIN|EPOLLET;//监听读状态同时设置ET模式
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, t->GetFd(), &ev);//注册epoll事件
	if (ret == -1)
	{
		std::cout << "epoll add client err" << std::endl;
		return -1;
	}
	
	timers.insert(make_pair(t->GetFd(), t));
	
	return 0;
}

int TimerManage::RemoveTimer(map<int, Timer *>::iterator it)
{
	struct epoll_event ev;
	int ret = -1;
	
	std::cout << "RemoveTimer:" << it->first << std::endl;
	ev.data.fd = it->first;                    
	//ev.events = EPOLLIN | EPOLLET;     
    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, it->first, &ev);
	if (ret == -1)
	{
		std::cout << "epoll del client err" << std::endl;
		return -1;
	}
	
	timers.erase(it);
	
	return 0;
}

int TimerManage::_Run()
{	
	int nfds, i, fd;
	struct epoll_event events[10];
	uint64_t howmany;
	map <int, Timer *>::iterator it;
					
	while (1)
    {
        nfds = epoll_wait(epfd, events, 10, -1);
        if (nfds == -1)
        {
			perror("epoll_wait");
            std::cout << "failed when epoll wait" << std::endl;
            continue;
        }
                
        for (i = 0; i < nfds; i++)
        {
            if (events[i].events & EPOLLIN) 
            {                            
				fd = events[i].data.fd;
								
				if (read(fd, &howmany, sizeof(howmany)) != sizeof(howmany))
				{
					std::cout << "read error\n" << std::endl;
					continue;
				}
				
				it = timers.find(fd);
				if (it == timers.end())
				{
					std::cout << "fd not found" << std::endl;
				}
				else
				{
					std::cout << "fd found" << std::endl;
					it->second->RunCallback();
					if (it->second->GetRepeat() == false)
					{
						RemoveTimer(it);
						delete it->second;
					}
				}
            }          
        }
    }
}

int TimerManage::Run()
{
	std::thread t(&_Run); 
	t.detach();
	
	return 0;
}

int TimerManage::Dump()
{
	std::cout << "Timers:" << timers.size() << std::endl;
	
	return 0;
}
