#ifndef PROC_METHOD_CPP
#define PROC_METHOD_CPP

#include "Method.hpp"


namespace wtk {
	namespace proc {

Method::Method(void) {}

Method::~Method(void) {}

std::string Method::GetName(void) {
	return this->_name;
}

void Method::SetName(std::string name) {
	this->_name = name;
}
	}
}


#endif
