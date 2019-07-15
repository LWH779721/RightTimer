#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "TimerManage.h"

using namespace RightTimer;
using namespace std;

int absCallback(void *userdata)
{
	std::cout << "end time" << std::endl;
	return 0;
}

int relCallback(void *userdata)
{
	struct timeval tv = {0};

	gettimeofday(&tv, NULL);

	cout << "time arvices " << tv.tv_sec <<	endl;
	
	return 0;
}

int abstime2ts(char *abstime)
{
	struct tm tmTemp;
	
	strptime(abstime, "%Y-%m-%d %H:%M:%S", &tmTemp);
	
	time_t t = mktime(&tmTemp);  
	
	return t;
}
	
int main(int argc, char **args)
{
	TimerManage *tm = TimerManage::GetTimerManager();
	int ts = abstime2ts("2019-5-29 11:14:11");
	
	tm->Start();
	
	cout << ts << endl;
	
	tm->AddTimer(true, ts, 0, absCallback, NULL);
	
	tm->Dump();
	
	tm->AddTimer(false, 1000, 10*1000, relCallback, NULL);
	
	tm->Dump();
	
	while (1)
	{
		sleep(1);
	}
	
	return 0;
}
