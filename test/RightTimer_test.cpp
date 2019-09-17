#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "TimerManager.h"
#include "TimerUtil.h"

using namespace RightTimer;
using namespace std;

int absCallback(void *userdata){
	std::cout << "end time" << std::endl;
	return 0;
}

int relCallback(void *userdata){
	struct timeval tv = {0};

	gettimeofday(&tv, NULL);

	cout << "time arvices " << tv.tv_sec <<	endl;
	
	return 0;
}
	
int main(int argc, char **args){
	TimerManager *tm = TimerManager::GetTimerManager();
	int ts = abstime2ts("2019-5-29 11:14:11");
	int timerfd1 = -1, timerfd2 = -1, timerfd3 = -1;
	
	cout << ts << endl;
	
	timerfd1 = tm->NewTimer(true, ts, 0, absCallback, NULL);
	
	tm->Dump();
	
	timerfd2 = tm->NewTimer(false, 1000, 10*1000, relCallback, NULL);
	
	tm->Dump();
	
	sleep(30);
	
	tm->PauseTimer(timerfd2);
	
	relCallback(NULL);
	timerfd3 = tm->NewTimer(false, 10*1000, 0, relCallback, NULL);
	cout << "I'm waiting for 10 second" << endl;
	
	while (1){
		sleep(1);
	}
	
	return 0;
}
