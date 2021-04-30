#ifndef TIME_CPP
#define TIME_CPP

#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <sys/select.h>
#include <time.h>
#include <cstdio>

#include "Time.hpp"

namespace wtk {
	namespace core {


void Time::Timestamp(std::string* timestamp) {
	char temp[128];

	struct tm *tmp = NULL; 
	time_t t;

	t = time(NULL);
	tmp = localtime(&t);
	sprintf(temp, "%04d%02d%02d%02d%02d%02d", 
			tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, 
			tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

	timestamp->clear();
	timestamp->assign(temp);
}

void Time::Daystamp(std::string* timestamp) {
	char temp[128];

	struct tm *tmp = NULL; 
	time_t t;

	t = time(NULL);
	tmp = localtime(&t);
	sprintf(temp, "%04d%02d%02d-%02d%02d%02d", 
			tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, 
			tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

	timestamp->clear();
	timestamp->assign(temp);
}

void Time::Datetime(std::string* timestamp) {
	char temp[128];

	struct tm *tmp = NULL; 
	time_t t;

	t = time(NULL);
	tmp = localtime(&t);
	sprintf(temp, "%04d.%02d.%02d-%02d:%02d:%02d", 
			tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, 
			tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

	timestamp->clear();
	timestamp->assign(temp);
}
		
void Time::Sleep(double ms) {
	timeval tm;
	tm.tv_sec = 0;
	tm.tv_usec = (long)1000*ms;

	select(0, NULL, NULL, NULL, &tm);
}

double Time::Sleep(double ms0, double ms1) {
	srand(time(NULL));
	double ms = rand()*(ms1-ms0)/RAND_MAX + ms0;
	Time::Sleep(ms);
	return ms;
}

void Time::Tic(TimeValue* tic) {
	gettimeofday(tic, NULL);
}

double Time::Toc(TimeValue* tic) {
	TimeValue toc;
	gettimeofday(&toc, NULL);

	return double((toc.tv_sec  - tic->tv_sec)*1000000 + 
			toc.tv_usec - tic->tv_usec)/1000;
}
		
void Time::Partial(TimeValue* tic, std::string step) {
	double elapsed = Time::Toc(tic);
	Time::Tic(tic);
	printf("[Time::Dump] %s: %f\n", step.c_str(), elapsed);
}
		
TimeValueHPT Time::HPT(void) {
	unsigned a, d;
	__asm__ volatile("rdtsc" : "=a" (a), "=d" (d));
	return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}

	}
}

#endif
