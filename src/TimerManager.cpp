#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/prctl.h>
#include <errno.h>

#include "TimerManager.h"

using namespace std;

extern int errno;

namespace RightTimer {

TimerManager* TimerManager::tm = NULL;

TimerManager::TimerManager():
		m_epfd(-1){
}

TimerManager* TimerManager::GetTimerManager(){
	if (NULL == tm){
		tm = new TimerManager();
		bool ret = tm->init();
		if (ret == false){
			delete tm;
			tm = NULL;
		}
	}
	
	return tm;
}

bool TimerManager::init(){
	m_epfd = epoll_create1(EPOLL_CLOEXEC);
    if (m_epfd == -1){
		cout << "err when epoll create" << endl;
        return false;
    }
	
	m_thread = std::thread(&TimerManager::ManageLoop, this);
	
	return true;
}

int TimerManager::NewTimer(bool abs, int delay, int interval, timer_callback cb, void *userdata){
	struct epoll_event ev;
	int ret = -1;
	Timer *t = new Timer;
	
	ret = t->Init(abs, delay, interval, cb, userdata);
	if (ret < 0){
		cout << "err when create timer" << endl;
		delete t;
		return -1;
	}
	
	std::cout << "AddTimer:" << t->m_timerfd << std::endl;
	m_timers.insert(make_pair(t->m_timerfd, t));
	
	ev.data.fd = t->m_timerfd;
    ev.events = EPOLLIN|EPOLLET;
    ret = epoll_ctl(m_epfd, EPOLL_CTL_ADD, t->m_timerfd, &ev);
	if (ret == -1){
		std::cout << "epoll add client err" << std::endl;
		delete t;
		return -1;
	}
	
	return t->m_timerfd;
}

int TimerManager::RemoveTimer(map<int, Timer *>::iterator it){
	struct epoll_event ev;
	int ret = -1;
	
	std::cout << "RemoveTimer:" << it->first << std::endl;
	ev.data.fd = it->first;                    
	//ev.events = EPOLLIN | EPOLLET;     
    ret = epoll_ctl(m_epfd, EPOLL_CTL_DEL, it->first, &ev);
	if (ret == -1){
		std::cout << "epoll del client err" << std::endl;
		return -1;
	}
	
	m_timers.erase(it);
	
	return 0;
}

bool TimerManager::PauseTimer(int timerfd){
	map <int, Timer *>::iterator it;
	
	it = m_timers.find(timerfd);
	if (it == m_timers.end()){
		cout << "can't found timer " << timerfd << endl;
		return false;
	}
	
	return it->second->Pause();
}

void TimerManager::ManageLoop(){	
	int nfds, i, fd;
	struct epoll_event events[10];
	uint64_t howmany;
	map <int, Timer *>::iterator it;
	
	prctl(PR_SET_NAME, "TimerManager");
	
	while (1){
        nfds = epoll_wait(m_epfd, events, 10, -1);
        if (nfds == -1){
			if (errno == EINTR)
				continue;
			else
				std::cout << "failed when epoll wait" << std::endl;
				continue;
        }
                
        for (i = 0; i < nfds; ++i){
            if (events[i].events & EPOLLIN){                            
				fd = events[i].data.fd;
								
				if (read(fd, &howmany, sizeof(howmany)) != sizeof(howmany)){
					std::cout << "read error" << std::endl;
					continue;
				}
				
				it = m_timers.find(fd);
				if (it == m_timers.end()){
					std::cout << "can't found timer " << fd << std::endl;
					continue;
				}

				it->second->RunCallback();
				if (it->second->GetRepeat() == false){
					RemoveTimer(it);
					delete it->second;
				}
            }          
        }
    }
}

int TimerManager::Dump(){
	map <int, Timer *>::iterator it;
	
	cout << "Timers:" << m_timers.size() << endl;
	it = m_timers.begin();
	while (it != m_timers.end()){
		cout << "Timer " << it->first << endl;	
		++it;
	}
	
	return 0;
}

TimerManager::~TimerManager(){
	if (m_thread.joinable()){
		m_thread.join();	
	}
}

}
