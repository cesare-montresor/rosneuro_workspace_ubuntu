#ifndef PROC_EXPONENTIALPD_CPP
#define PROC_EXPONENTIALPD_CPP

#include "ExponentialPd.hpp"
#include <iostream>

using namespace std;

namespace wtk {
	namespace proc {

ExponentialPd::ExponentialPd(double alpha, double alpha_control, unsigned int nclasses) : Algorithm(Algorithm::AsExpAccumulation) {
	this->SetAlpha(alpha);
	this->SetNumClasses(nclasses);

	this->_prevprobs = Eigen::VectorXd::Zero(nclasses);
  this->_udist = 1.0/this->_nclasses;

  this->control_exponential_ = Exponential(alpha_control, nclasses);
  this->_prevcontrolprobs = Eigen::VectorXd::Zero(nclasses);

	this->Reset();
  this->control_exponential_.Reset();
}

ExponentialPd::~ExponentialPd(void) {}

double ExponentialPd::GetAlpha(void) {
	return this->_alpha;
}

void ExponentialPd::SetAlpha(double alpha) {
	this->_alpha = alpha;
}

double ExponentialPd::GetControlAlpha(void) {
  return this->control_exponential_.GetAlpha();
}

void ExponentialPd::SetControlAlpha(double alpha) {
  this->control_exponential_.SetAlpha(alpha);
}

unsigned int ExponentialPd::GetNumClasses(void) {
	return this->_nclasses;
}

void ExponentialPd::SetNumClasses(unsigned int nclasses) {
	this->_nclasses = nclasses;
  this->control_exponential_.SetNumClasses(nclasses);
}

void ExponentialPd::Reset(void) {
	this->_prevprobs.fill(this->_udist);
  this->_prevcontrolprobs.fill(this->_udist);
  this->control_exponential_.Reset();
}

void ExponentialPd::Apply(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

	double alpha 	      = this->GetAlpha();
	//unsigned int nclasses = this->GetNumClasses();
	out = alpha * this->_prevprobs + (1.0 - alpha) * in;

	this->_prevprobs = out;

}

void ExponentialPd::ApplyPd(const Eigen::Ref<const Eigen::VectorXd>& in,
                            const Eigen::Ref<const Eigen::VectorXd>& in_control,
                            Eigen::Ref<Eigen::VectorXd> out,
                            Eigen::Ref<Eigen::VectorXd> out_control) {

  double alpha 	      = this->GetAlpha();
  unsigned int nclasses = this->GetNumClasses();

  Eigen::VectorXd ippcontrol = Eigen::VectorXd::Zero(nclasses);
  this->control_exponential_.Apply(in_control, ippcontrol);

  double pp = in(0);


  /*

  if (ippcontrol(0) > 0) {

    out(0) = alpha * this->_prevprobs(0) + (1.0 - alpha) * pp;
  } else {
    out(0) = this->_prevprobs(0);
  }*/

  double cf = std::copysign( 1.0, (pp - 0.5)) * ( (1 - ippcontrol(0)) * 0.5 - (0.5 - std::abs(pp - 0.5))) *
      (1 - std::abs(ippcontrol(0) - this->_prevcontrolprobs(0)));

  out(0) = alpha * this->_prevprobs(0) + (1.0 - alpha) * (pp - cf);
  out(1) = 1 - out(0);

  out_control = ippcontrol;

  this->_prevcontrolprobs = ippcontrol;
  this->_prevprobs = out;

}
	}
}

#endif
