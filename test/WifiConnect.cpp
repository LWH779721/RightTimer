#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include "WifiConnect.h"

using namespace std;

WifiConnect::WifiConnect(string name){
	m_timer = std::make_shared<Timer>(name);
    
	m_timer->setTarget(1, 0);
	m_timer->setCallback(bind(&WifiConnect::Run, this));
	
    m_timer->start();
}

void WifiConnect::Run(){
	struct timeval tv = {0};

	gettimeofday(&tv, NULL);

	cout << "time arvices : sec:" << tv.tv_sec << " nsec: " << tv.tv_usec << endl;
	
	m_timer->setTarget(10, 0);
	m_timer->setInterval(1, 10*1000);
	m_timer->setCallback(bind(&WifiConnect::Run1, this));
	m_timer->start();
}

void WifiConnect::Run1(){
	struct timeval tv = {0};
    static int count;
    
    count++;
    if (count == 5){
        m_timer->stop();
        return;
    }
    
	gettimeofday(&tv, NULL);

	cout << "time arvices : sec:" << tv.tv_sec << " nsec: " << tv.tv_usec << endl;
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
