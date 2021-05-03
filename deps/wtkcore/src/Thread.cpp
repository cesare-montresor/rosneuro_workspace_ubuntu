#ifndef THREAD_CPP
#define THREAD_CPP

#include "Thread.hpp"
#include "Threadrunner.hpp"

namespace wtk {
	namespace core {


Thread::Thread(void) {
	this->running_ = false;
}

Thread::~Thread(void) {
	if(this->IsRunning() == true) {
		this->Stop();
		this->Join();
	}
}

void Thread::Start(void) {
	this->pBeforeStart();
	this->semstatus_.Wait();
	if(this->running_ == true) {
		this->semstatus_.Post();
		return;
	}

	this->semthread_.Wait();
	int status = 0;
	status = pthread_create(&this->thread_, NULL, wtk::core::Threadrunner, (void *)this);
	this->running_ = (status == 0);
	this->started_ = (status == 0);
	this->semthread_.Post();
	this->semstatus_.Post();
	this->pAfterStart();
}

void Thread::Stop(void) {
	this->pBeforeStop();
	this->semstatus_.Wait();
	this->running_ = false;
	this->semstatus_.Post();
	this->pAfterStop();
}

int Thread::Join(void) {
	int status = -1;
	
	this->semthread_.Wait();
	bool started = this->started_;
	this->semthread_.Post();

	if(started == true) {
		status = pthread_join(this->thread_, NULL);
		this->started_ = (status == 0);
	}
	return status;
}
		
bool Thread::IsRunning(void) { 	
	this->semstatus_.Wait();
	bool status = this->running_;
	this->semstatus_.Post();

	return status;
}

	}
}
		
#endif
