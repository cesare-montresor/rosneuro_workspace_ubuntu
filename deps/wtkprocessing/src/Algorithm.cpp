#ifndef PROC_ALGORITHM_CPP
#define PROC_ALGORITHM_CPP

#include "Algorithm.hpp"

namespace wtk {
	namespace proc {


Algorithm::Algorithm(int type)  {
	this->_type = type;
}

Algorithm::~Algorithm(void) {
}

int Algorithm::GetType(void) {
	return this->_type;
}

void Algorithm::SetType(int type) {
	this->_type = type;
}

std::string Algorithm::GetName(void) {
	return this->_name;
}

void Algorithm::SetName(std::string name) {
	this->_name = name;
}

	}
}
#endif
