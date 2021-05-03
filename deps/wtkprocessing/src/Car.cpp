#ifndef PROC_CAR_CPP
#define PROC_CAR_CPP

#include "Car.hpp"

namespace wtk {
	namespace proc {

Car::Car(void) : Filter(Filter::inDomainSpatial) {
	this->_name = "car";
}
Car::~Car(void) {}

void Car::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out) {
	out = in - (in.rowwise().mean()).replicate(1, in.cols());
}

	}
}

#endif
