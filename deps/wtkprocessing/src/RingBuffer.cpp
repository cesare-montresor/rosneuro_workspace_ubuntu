#ifndef PROC_RINGBUFFER_CPP
#define PROC_RINGBUFFER_CPP

#include "RingBuffer.hpp"

namespace wtk {
	namespace proc {

RingBuffer::RingBuffer() : Buffer(Buffer::AsRingBuffer) {
	this->_isset = false;
}

RingBuffer::~RingBuffer(void) {
}

bool RingBuffer::Setup(unsigned int numsamples, unsigned int numchannels) {
	this->_buffer = Eigen::MatrixXd(numsamples, numchannels);
	this->_buffer.fill(NAN);

	this->_isset = true;

	return this->_isset;
}

void RingBuffer::Add(const Eigen::Ref<const Eigen::MatrixXd>& in) {

	try {

		this->IsSet();
		
		unsigned int FSamples = in.rows();
		unsigned int FChannels = in.cols();
		unsigned int BSamples = this->_buffer.rows();
		unsigned int BChannels = this->_buffer.cols();
		
		proc_check_dim(BChannels, FChannels, "Buffer dimensions inconsistent");	
		
		Eigen::MatrixXd cbuff(BSamples - FSamples, BChannels);
		cbuff = this->_buffer.bottomRows(BSamples - FSamples);

		this->_buffer << cbuff, in;
	} catch (wtk::core::Exception& e) {
		printf("%s\n", e.Info().c_str());
	}
}
	}
}


#endif
