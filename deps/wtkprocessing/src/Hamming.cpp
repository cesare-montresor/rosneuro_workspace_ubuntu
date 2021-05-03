#ifndef PROC_HAMMING_CPP
#define PROC_HAMMING_CPP

#include "Hamming.hpp"

namespace wtk {
	namespace proc {

Hamming::Hamming(unsigned int numsamples) : Window(Window::AsHamming) {

	this->_wname = "Hamming";

	this->_numsamples = numsamples;
	this->_window = Eigen::VectorXd::Zero(this->_numsamples);
	
	for(unsigned int i = 0; i<this->_numsamples; i++)
		this->_window(i)   = (54.0 - 46.0*cos((2.0 * M_PI * i)/(this->_numsamples-1))) / 100.0;

	this->_windownorm = ComputeNorm();
}

Hamming::~Hamming(void) {}
	}
}
#endif
