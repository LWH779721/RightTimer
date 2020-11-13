#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "Alarm.h"

using namespace TimeWalker;
using namespace std;

Alarm::Alarm(string name){
    m_timer = std::make_shared<RealTimer>(name, true, 0, 0, 0, 0, bind(&Alarm::Run, this));
	
    m_timer->Start("2020-05-27 21:07:30");
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
