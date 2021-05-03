#ifndef XEXCEPTION_CPP
#define XEXCEPTION_CPP

#include "XException.hpp"

namespace wtk {
	namespace xml {

XException::XException(std::string info, std::string caller) {
	this->_info = info;
	this->_caller = caller;
}

XException::~XException(void) {
}

std::string XException::Caller(void) const {
	return this->_caller;
}

std::string XException::Info(void) const {
	return this->_info;
}

std::ostream &operator<<(std::ostream& output, const XException& obj) {
	output << std::string("[") << obj.Caller() << std::string("] ") 
		<< obj.Info();
	return output;
}

std::ostream &operator<<(std::ostream& output, const XException* obj) {
	output << std::string("[") << obj->Caller() << std::string("] ") 
		<< obj->Info();
	return output;
}
	
bool XException::operator==(const XException& right) {
	return(this->_info.compare(right.Info()) == 0);
}

bool XException::operator!=(const XException& right) {
	return(this->_info.compare(right.Info()) != 0);
}

	}
}

#endif
