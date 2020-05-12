#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "WifiConnect.h"

using namespace std;

WifiConnect::WifiConnect(string name){
	m_timer = std::make_shared<MonotonicTimer>(name, false, 0, 0, 1, 0, bind(&WifiConnect::Run, this));
	
    m_timer->Start();
}

void WifiConnect::Run(){
	struct timeval tv = {0};

	gettimeofday(&tv, NULL);

	cout << "time arvices " << tv.tv_sec <<	endl;
	m_timer->Reset(false, 10, 0, 1, 0, bind(&WifiConnect::Run1, this));
}

void WifiConnect::Run1(){
	struct timeval tv = {0};

	gettimeofday(&tv, NULL);

	cout << "time1 arvices " << tv.tv_sec <<	endl;
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
