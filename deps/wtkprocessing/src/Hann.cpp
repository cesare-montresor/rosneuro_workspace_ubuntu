#ifndef PROC_HANN_CPP
#define PROC_HANN_CPP

#include "Hann.hpp"

namespace wtk {
	namespace proc {

Hann::Hann(unsigned int numsamples) : Window(Window::AsHann) {

	this->_wname = "Hann";

	this->_numsamples = numsamples;
	this->_window = Eigen::VectorXd::Zero(this->_numsamples);

	for(unsigned int i = 0; i<this->_numsamples; i++)
		this->_window(i)   = (1.0 - cos((2.0 * M_PI * i)/(this->_numsamples-1))) * 0.5;
	
	this->_windownorm = ComputeNorm();
}

Hann::~Hann(void) {}
	}
}
#endif
