#ifndef PROC_FLATTOP_CPP
#define PROC_FLATTOP_CPP

#include "Flattop.hpp"

namespace wtk {
	namespace proc {

Flattop::Flattop(unsigned int nsamples) : Window(Window::AsFlattop) {
	
	double a0 = BCITK_WIN_FLTP_A0;
    	double a1 = BCITK_WIN_FLTP_A1;
    	double a2 = BCITK_WIN_FLTP_A2;
    	double a3 = BCITK_WIN_FLTP_A3;
    	double a4 = BCITK_WIN_FLTP_A4;		
	
	this->_wname = "Flattop";
	this->_numsamples = nsamples;
	this->_window = Eigen::VectorXd::Zero(this->_numsamples);
	
	for(unsigned int i = 0; i<this->_numsamples; i++)
		this->_window(i)   = a0 - a1*cos((2.0 * M_PI * i)/(this->_numsamples-1)) + a2*cos((4.0 * M_PI * i)/(this->_numsamples-1)) - a3*cos((6.0 * M_PI * i)/(this->_numsamples-1)) + a4*cos((8.0 * M_PI * i)/(this->_numsamples-1));

	this->_windownorm = ComputeNorm();
}

Flattop::~Flattop(void) {}
	}
}

#endif
