#ifndef PROC_BLACKMAN_CPP
#define PROC_BLACKMAN_CPP

#include "Blackman.hpp"

namespace wtk {
	namespace proc {

Blackman::Blackman(unsigned int numsamples) : Window(Window::AsBlackman) {
	
	this->_wname = "Blackman";

	this->_numsamples = numsamples;
	this->_window = Eigen::VectorXd::Zero(this->_numsamples);
	
	for(unsigned int i = 1; i<this->_numsamples; i++)
		this->_window(i)   = (42.0 - 50.0*cos((2.0 * M_PI * i)/(this->_numsamples-1)) + 8.0*cos((4.0 * M_PI * i)/(this->_numsamples - 1))) / 100.0;

	this->_window(0) = 0.0;
	this->_windownorm = ComputeNorm();
}

Blackman::~Blackman(void) {}
	}
}

#endif
