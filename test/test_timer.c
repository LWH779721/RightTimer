#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/timerfd.h>
#include <sys/time.h>
#include <inttypes.h>

#include "time/mtimeStamp.h"
 
#ifndef INFTIM
#define INFTIM -1
#endif	

int test_precision()
{
	struct timeval delay;// = {0, 1000};
	struct timespec ts;
	
	uint64_t start = 0, end = 0;
	
	delay.tv_sec = 1;
	delay.tv_usec = 1000;
	
	ts.tv_nsec = 0;    
    ts.tv_sec = 1;
	
	while (1)
	{
		start = mts_get_real_uts();
		select(0, NULL, NULL, NULL, &delay);
		end = mts_get_real_uts();
		printf("select precision: %"PRIu64", %"PRIu64", %"PRIu64"\n", end, start, end - start);
		
		start = mts_get_real_uts();
		sleep(1);
		end = mts_get_real_uts();
		printf("sleep precision: %"PRIu64", %"PRIu64", %"PRIu64"\n", end, start, end - start);
		
		start = mts_get_real_uts();
		usleep(1*1000*1000);
		end = mts_get_real_uts();
		printf("usleep precision: %"PRIu64", %"PRIu64", %"PRIu64"\n", end, start, end - start);
		
		start = mts_get_real_uts();
		nanosleep(&ts, NULL);
		end = mts_get_real_uts();
		printf("nanosleep precision: %"PRIu64", %"PRIu64", %"PRIu64"\n", end, start, end - start);
	}	
	
	return 0;
}

int RealTimeTimer()
{
	int timerfd;
 
	timerfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
	if (timerfd < 0)
	{
		printf("timerfd_create error\n");
		return -1;
	}
	
	struct itimerspec new_value = {0};
 
	new_value.it_value.tv_sec = 1557999229;
	new_value.it_value.tv_nsec = 0;
 
	if (timerfd_settime(timerfd, TFD_TIMER_ABSTIME, &new_value, NULL) != 0)
	{
		printf("timerfd_settime error\n");
		close(timerfd);
		return -1;
	}
	
	struct pollfd fdPoll;
	fdPoll.fd = timerfd;
	fdPoll.events = POLLIN;
 
	while (1)
	{
		if (poll(&fdPoll, 1, INFTIM) < 0)
		{
			printf("poll error\n");
			break;
		}
 
		if (fdPoll.revents & POLLIN)
		{
			uint64_t howmany;	
			if (read(timerfd, &howmany, sizeof(howmany)) != sizeof(howmany))
			{
				printf("read error\n");
				break;
			}
			#if 0
			static uint64_t old = 0;
			uint64_t now = 0;
			
			now = mts_get_real_uts();
			printf("timerfd %llu, Timer 5s\n", now - old);
			
			old = now;
			#else
				printf("read: %llu\n", (unsigned long long)howmany);
			#endif
		}
	}
 
	close(timerfd);
	return 0;
}
 
int main(void)
{
	//test_precision();
	RealTimeTimer();
	return 0;
	
	int iFd;
 
	iFd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC | TFD_NONBLOCK);
	if (iFd < 0)
	{
		printf("timerfd_create error\n");
		return -1;
	}
 
	struct itimerspec new_value;
	
	new_value.it_interval.tv_sec = 1;
	new_value.it_interval.tv_nsec = 0;
 
	new_value.it_value.tv_sec = 1;
	new_value.it_value.tv_nsec = 0;
 
	if (timerfd_settime(iFd, 0, &new_value, NULL) != 0)
	{
		printf("timerfd_settime error\n");
		close(iFd);
		return -1;
	}
 
	struct pollfd fdPoll;
	fdPoll.fd = iFd;
	fdPoll.events = POLLIN;
 
	while (1)
	{
		if (poll(&fdPoll, 1, INFTIM) < 0)
		{
			printf("poll error\n");
			break;
		}
 
		if (fdPoll.revents & POLLIN)
		{
			uint64_t howmany;	
			if (read(iFd, &howmany, sizeof(howmany)) != sizeof(howmany))
			{
				printf("read error\n");
				break;
			}
			#if 0
			static uint64_t old = 0;
			uint64_t now = 0;
			
			now = mts_get_real_uts();
			printf("timerfd %llu, Timer 5s\n", now - old);
			
			old = now;
			#else
				printf("read: %llu\n", (unsigned long long)howmany);
			#endif
		}
	}
 
	close(iFd);
 
	return 0;
}

