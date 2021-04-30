#ifndef SEMAPHORE_CPP
#define SEMAPHORE_CPP

#include "Semaphore.hpp"

namespace wtk {
	namespace core {

Semaphore::Semaphore(unsigned int count) {
	sem_init(&this->semaphore_, 0, count);
}

Semaphore::~Semaphore(void) {
	sem_destroy(&this->semaphore_);
}
		
void Semaphore::Wait(void) {
	sem_wait(&this->semaphore_);
}

void Semaphore::Post(void) {
	sem_post(&this->semaphore_);
}

bool Semaphore::TryWait(void) {
	if(sem_trywait(&this->semaphore_) == 0)
		return true;
	else
		return false;
}

	}
}

#endif
