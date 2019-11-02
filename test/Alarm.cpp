#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "Alarm.h"

using namespace RightTimer;
using namespace std;

Alarm::Alarm(string name):RealTimer(name){
	Init();
	
	TimerDetector *tm = TimerDetector::GetDefaultDetector();
	tm->DetectTimer(this);
	
	int ts = abstime2ts("2019-11-2 16:58:11");
	std::cout << ts << std::endl;
	Start(true, ts, 0, 0, 0);
	
	tm->Dump();
}

void Alarm::Run(){
	struct timeval tv = {0};

	gettimeofday(&tv, NULL);

	cout << "time arvices " << tv.tv_sec <<	endl;
}

Alarm::~Alarm(){
}
	
int main(int argc, char **args){
	Alarm a("alarm");
	
	while (1){
		sleep(1);
	}
	
	return 0;
}
