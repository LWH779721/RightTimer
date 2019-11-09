#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "WifiConnect.h"

using namespace RightTimer;
using namespace std;

WifiConnect::WifiConnect(string name):MonotonicTimer(name){
	Init(false, 0, 1, 1, 0);
	
	TimerDetector *tm = TimerDetector::GetDefaultDetector();
	tm->DetectTimer(this);
	//Run();
	Start();
	
	tm->Dump();
}

void WifiConnect::Run(){
	struct timeval tv = {0};

	gettimeofday(&tv, NULL);

	cout << "time arvices " << tv.tv_sec <<	endl;
}

WifiConnect::~WifiConnect(){
}
	
int main(int argc, char **args){
	WifiConnect *a = new WifiConnect("wifiConnect");
	
	//delete a;
	while (1){
		sleep(1);
	}
	
	return 0;
}
