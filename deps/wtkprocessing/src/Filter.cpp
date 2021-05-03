#ifndef PROC_FILTER_CPP
#define PROC_FILTER_CPP

#include "Filter.hpp"

namespace wtk {
	namespace proc {

Filter::Filter(int domain) {
	this->_domain = domain;
}

Filter::~Filter(void) {
}

int Filter::GetDomain(void) {
	return this->_domain;	
}

std::string Filter::GetDomainName(void) {
	
	std::string name;

	switch(this->_domain) {
		case Filter::inDomainSpatial:
			name = "Spatial";
			break;
		case Filter::inDomainTime:
			name = "Time";
			break;
		case Filter::inDomainFrequency:
			name = "Frequency";
			break;
		case Filter::inDomainGeneric:
			name = "Generic";
			break;
		default:
			name = "Undefined";
			break;
	}

	return name;
}

std::string Filter::GetName(void) {
	return this->_name;
}

void Filter::SetName(std::string name) {
	this->_name = name;
}
	}
}

#endif
