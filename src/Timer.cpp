#include <iostream>
#include <unistd.h>
#include <sys/timerfd.h>

#include "TimerDetector.h"
#include "Timer.h"

using namespace std;

namespace TimeWalker {
	
Timer::Timer(string name):
	TimeWalker(name, TimeType::MONOTONIC, TimeRelation::RELATIVE){
}

Timer::~Timer(){

}
}
