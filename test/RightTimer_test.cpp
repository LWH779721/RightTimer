#include <iostream>
#include <unistd.h>

#include "RightTimer.hpp"

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
	RightTimer::TimerManage tm;
	
	tm.Init();
	int ts = abstime2ts("2019-3-12 16:39:11");
	
	std::cout << ts << std::endl;
	
	tm.Run();
	
	tm.AddTimer(true, ts, 0, absCallback);
	
	while (1)
	{
		sleep(1);
	}
	
	return 0;
}
