#ifndef PROC_EXPONENTIAL_CPP
#define PROC_EXPONENTIAL_CPP

#include "Exponential.hpp"

using namespace std;

namespace wtk {
	namespace proc {

Exponential::Exponential(double alpha, unsigned int nclasses) : Algorithm(Algorithm::AsExpAccumulation) {
	this->SetAlpha(alpha);
	this->SetNumClasses(nclasses);

	this->_prevprobs = Eigen::VectorXd::Zero(nclasses);
	this->_udist = 1.0/this->_nclasses; 
	this->Reset();
}

Exponential::~Exponential(void) {}

double Exponential::GetAlpha(void) {
	return this->_alpha;
}

void Exponential::SetAlpha(double alpha) {
	this->_alpha = alpha;
}

unsigned int Exponential::GetNumClasses(void) {
	return this->_nclasses;
}

void Exponential::SetNumClasses(unsigned int nclasses) {
	this->_nclasses = nclasses;
}

void Exponential::Reset(void) {
	this->_prevprobs.fill(this->_udist);
}

void Exponential::Apply(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

	double alpha 	      = this->GetAlpha();
  //unsigned int nclasses = this->GetNumClasses();
	out = alpha * this->_prevprobs + (1.0 - alpha) * in;

	this->_prevprobs = out;

}
	}
}

#endif
