#ifndef PROC_BUFFER_CPP
#define PROC_BUFFER_CPP

#include "Buffer.hpp"

namespace wtk {
	namespace proc {

Buffer::Buffer(int type) {
	this->_type = type;
	this->_isset = false;
}

Buffer::~Buffer(void) {}

int Buffer::GetType(void) {
	return this->_type;
}

void Buffer::Get(Eigen::Ref<Eigen::MatrixXd> out) {
	out = this->_buffer;
}

bool Buffer::IsFull(void) {
	return !(this->_buffer.hasNaN());
}

bool Buffer::IsSet(void) {
	if(this->_isset == false)
		throw wtk::core::Exception("The buffer is not setup");

	return this->_isset;
}

void Buffer::Dump(void) {
	std::cout<< this->_buffer << std::endl;
}

	}
}

#endif
