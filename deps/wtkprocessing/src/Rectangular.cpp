#ifndef PROC_RECTANGULAR_CPP
#define PROC_RECTANGULAR_CPP

#include "Rectangular.hpp"

namespace wtk {
    namespace proc {

Rectangular::Rectangular(unsigned int numsamples) : Window(Window::AsRectangular) {

    this->_wname = "Rectangular";

    this->_numsamples = numsamples;
    this->_window = Eigen::VectorXd::Ones(this->_numsamples);

    this->_windownorm = ComputeNorm();
}

Rectangular::~Rectangular(void) {}
    }
}
#endif
