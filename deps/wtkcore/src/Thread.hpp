#ifndef THREAD_HPP
#define THREAD_HPP

#include "Semaphore.hpp"
#include <pthread.h>

namespace wtk {
	namespace core {


class Thread {
	public:
		Thread(void);
		virtual ~Thread(void);
		virtual void Main(void) = 0;
		void Start(void);
		void Stop(void);
		void Wait(void);
		int Join(void);
		bool IsRunning(void);
		bool IsStarted(void);
	protected:
		virtual void pBeforeStart(void) {};
		virtual void pAfterStart(void) {};
		virtual void pBeforeStop(void) {};
		virtual void pAfterStop(void) {};
	
	private:
		wtk::core::Semaphore semstatus_;
		wtk::core::Semaphore semthread_;
		bool running_;
		bool started_;
		pthread_t thread_;
};

	}
}

#endif
