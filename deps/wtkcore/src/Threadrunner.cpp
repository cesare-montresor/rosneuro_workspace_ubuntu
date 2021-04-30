#ifndef THREADRUNNER_CPP
#define THREADRUNNER_CPP

#include "Threadrunner.hpp"

namespace wtk {
	namespace core {


void* Threadrunner(void* implementation) {
	wtk::core::Thread *runner = (wtk::core::Thread *)implementation;
	runner->Main();
	
	return NULL;
}

	}
}

#endif
