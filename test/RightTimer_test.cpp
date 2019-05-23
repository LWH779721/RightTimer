#include <iostream>
#include <unistd.h>

#include "TimerManage.hpp"

using namespace RightTimer;
using namespace std;

int absCallback(Timer &timer)
{
	std::cout << "end time" << std::endl;
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
	int ts = abstime2ts("2019-5-23 20:14:11");
	
	tm->Start();
	
	std::cout << ts << std::endl;
	
	tm->AddTimer(true, ts, 0, absCallback);
	
	while (1)
	{
		sleep(1);
	}
	
	return 0;
}
