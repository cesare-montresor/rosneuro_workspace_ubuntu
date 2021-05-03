#ifndef PROC_CLASSIFIER_CPP
#define PROC_CLASSIFIER_CPP

#include "Classifier.hpp"

namespace wtk {
	namespace proc {

Classifier::Classifier(int type) {
	this->_type = type;
}

Classifier::~Classifier(void) {}

int Classifier::GetType(void) {
	return this->_type;
}

void Classifier::SetName(std::string name) {
	this->_name = name;
}

std::string Classifier::GetName(void) {
	return this->_name;
}

	}
}

#endif
