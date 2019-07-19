#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "TimerUtil.h"

namespace RightTimer {

using namespace std;

int abstime2ts(const string& abstime){
	struct tm tmTemp;
	
	strptime(abstime.c_str(), "%Y-%m-%d %H:%M:%S", &tmTemp);
	
	time_t t = mktime(&tmTemp);  
	
	return t;
}

};
