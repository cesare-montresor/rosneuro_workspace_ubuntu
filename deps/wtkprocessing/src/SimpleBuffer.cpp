//#ifndef PROC_SIMPLEBUFFER_CPP
//#define PROC_SIMPLEBUFFER_CPP

#include "SimpleBuffer.hpp"

namespace wtk {
	namespace proc {

SimpleBuffer::SimpleBuffer() : Buffer(Buffer::AsSimpleBuffer) {
	this->_isset = false;
}

SimpleBuffer::~SimpleBuffer(void) {
}

bool SimpleBuffer::Setup(unsigned int numsamples, unsigned int numchannels) {
	this->_buffer = Eigen::MatrixXd(numsamples, numchannels);
	this->_buffer.fill(NAN);

	this->_isset = true;

	return this->_isset;
}

void SimpleBuffer::Add(const Eigen::Ref<const Eigen::MatrixXd>& in) {

	
	try {

    IsSet();
    if(this->IsFull()) throw std::runtime_error("The buffer is over the size");
		unsigned int FSamples = in.rows();
		unsigned int FChannels = in.cols();
		unsigned int BSamples = this->_buffer.rows();
		unsigned int BChannels = this->_buffer.cols();
		
		proc_check_dim(BChannels, FChannels, "Buffer dimensions inconsistent");	
		
    std::cout<<"SIMPLE_BUFFER: CHECK THE DIMENSION OF THE inSAMPLES" << FSamples << std::endl;

    Eigen::MatrixXd cbuff(BSamples - FSamples, BChannels);
    cbuff = this->_buffer.bottomRows(BSamples - FSamples);

    this->_buffer << cbuff, in;
	} catch (wtk::core::Exception& e) {
		printf("%s\n", e.Info().c_str());
	}
}

void SimpleBuffer::Reset(void)
{
  this->_buffer.fill(NAN);
}

	}
}


//#endif
