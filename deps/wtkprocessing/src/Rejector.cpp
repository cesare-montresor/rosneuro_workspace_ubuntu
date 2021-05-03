#ifndef PROC_REJECTOR_CPP
#define PROC_REJECTOR_CPP

#include "Rejector.hpp"

namespace wtk {
	namespace proc {

Rejector::Rejector(double rejection, unsigned int nclasses, int modality) : Algorithm(Algorithm::AsRejector) {
	this->_rejection = rejection;
	this->_nclasses  = nclasses;
	this->_modality  = modality;
	
	this->_values   = Eigen::VectorXd::Zero(this->_nclasses);
	this->_values.fill(1.0/this->_nclasses);
}

Rejector::~Rejector(void) {
}

double Rejector::GetRejection(void) {
	return this->_rejection;
}

void Rejector::SetRejection(double rejection) {
	this->_rejection = rejection;
}

void Rejector::GetValues(Eigen::Ref<Eigen::VectorXd> values) {
	values = this->_values;
}

void Rejector::SetValues(const Eigen::Ref<const Eigen::VectorXd>& values) {
	this->_values = values;
}

int Rejector::GetModality(void) {
	return this->_modality;
}

void Rejector::SetModality(int modality) {
	this->_modality = modality;
}

void Rejector::Reset(void) {
	this->_values.fill(1.0/this->_nclasses);
}

void Rejector::Apply(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

	double rejection = this->GetRejection();
	
	out = in;

	if (in.maxCoeff() < rejection) {
		out = this->_values;
	}

	
	if (this->_modality == Rejector::AsRecursive) {
		this->_values = out;
	}
}
	}
}


#endif
