#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>

#include "TimerManage.h"

using namespace std;

extern int errno;

namespace RightTimer {

TimerManage* TimerManage::tm = NULL;

TimerManage::TimerManage():
		m_epfd(-1){
}

TimerManage* TimerManage::GetTimerManager(){
	if (NULL == tm){
		tm = new TimerManage();
		bool ret = tm->init();
		if (ret == false){
			delete tm;
			tm = NULL;
		}
	}
	
	return tm;
}

bool TimerManage::init(){
	m_epfd = epoll_create1(EPOLL_CLOEXEC);
    if (m_epfd == -1){
		cout << "err when epoll create" << endl;
        return false;
    }
	
	m_thread = std::thread(&TimerManage::ManageLoop, this);
	
	return true;
}

int TimerManage::NewTimer(bool abs, int delay, int interval, timer_callback cb, void *userdata){
	struct epoll_event ev;
	int tfd = -1;
	int ret = -1;
	Timer *t = new Timer;
	
	ret = t->Init(abs, delay, interval, cb, userdata);
	if (ret < 0){
		cout << "err when create timer" << endl;
		return -1;
	}
	
	tfd = t->GetFd();
	std::cout << "AddTimer:" << tfd << std::endl;
	timers.insert(make_pair(tfd, t));
	
	ev.data.fd = tfd;
    ev.events = EPOLLIN|EPOLLET;
    ret = epoll_ctl(m_epfd, EPOLL_CTL_ADD, tfd, &ev);
	if (ret == -1){
		std::cout << "epoll add client err" << std::endl;
		return -1;
	}
	
	return 0;
}

int TimerManage::RemoveTimer(map<int, Timer *>::iterator it){
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
	
	timers.erase(it);
	
	return 0;
}

void TimerManage::ManageLoop(){	
	int nfds, i, fd;
	struct epoll_event events[10];
	uint64_t howmany;
	map <int, Timer *>::iterator it;
					
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
				
				it = timers.find(fd);
				if (it == timers.end()){
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

int TimerManage::Dump(){
	map <int, Timer *>::iterator it;
	
	cout << "Timers:" << timers.size() << endl;
	it = timers.begin();
	while (it != timers.end()){
		cout << "Timer " << it->first << endl;	
		++it;
	}
	
	return 0;
}

TimerManage::~TimerManage(){
	if (m_thread.joinable()){
		m_thread.join();	
	}
}

}
