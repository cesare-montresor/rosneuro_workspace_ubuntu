#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <pthread.h>
#include <semaphore.h>

namespace wtk {
	namespace core {

class Semaphore {
	public:
		Semaphore(unsigned int count = 1);
		~Semaphore(void);

		void Wait(void);
		void Post(void);
		bool TryWait(void);

	protected:
		sem_t semaphore_;
};

	}
}
#endif
