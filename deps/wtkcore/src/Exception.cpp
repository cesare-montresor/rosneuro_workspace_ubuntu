#ifndef EXCEPTION_CPP
#define EXCEPTION_CPP

#include "Exception.hpp"

namespace wtk {
	namespace core {

Exception::Exception(std::string info, std::string caller) {
	this->_info = info;
	this->_caller = caller;
	this->CreateMessage();
}

Exception::~Exception(void) {
}

std::string Exception::Caller(void) const {
	return this->_caller;
}

std::string Exception::Info(void) const {
	return this->_info;
}

std::string Exception::Message(void) const {
	return this->_message;
}

void Exception::CreateMessage(void) {
	this->_message.append("[");
	this->_message.append(this->_caller);
	this->_message.append("] ");
	this->_message.append(this->_info);
}

std::ostream &operator<<(std::ostream& output, const Exception& obj) {
	output << "[Exception] " << obj.Message();
	return output;
}

std::ostream &operator<<(std::ostream& output, const Exception* obj) {
	output << "[Exception] " << obj->Message();
	return output;
}
	
bool Exception::operator==(const Exception& right) {
	return(this->_info.compare(right.Info()) == 0);
}

bool Exception::operator!=(const Exception& right) {
	return(this->_info.compare(right.Info()) != 0);
}
	}
}

#endif
