#ifndef PROC_PADDING_CPP
#define PROC_PADDING_CPP

#include "Padding.hpp"

namespace wtk {
	namespace proc {

Padding::Padding(void) {
	this->_isset = false;
}

Padding::~Padding(void) {
}

bool Padding::Setup(unsigned int padding_type, unsigned int n_samples) {
	
	try {
		this->padding_type = padding_type;
		this->nsamples = n_samples;

		this->_isset = true;

	} catch (wtk::core::Exception& e) {
		printf("%s\n", e.Info().c_str());
	}

	return this->IsSet();

}

bool Padding::IsSet(void) {
	if(this->_isset == false)
		throw wtk::core::Exception("The padding is not setup");

	return this->_isset;
}

void Padding::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out){


	unsigned int nchannels = in.cols();

	for (unsigned int i = 0; i < nchannels; i++) {
		compute(in.col(i), out.col(i));
	}
}


void Padding::compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

	// Edited by L.Tonin  <luca.tonin@epfl.ch> on 22/07/19 12:34:22
	// Changed || to &&
	if( (this->padding_type != 1) && (this->padding_type != 2))
		throw wtk::core::Exception("The padding type is not correct");

	switch(this->padding_type) {
                        case 1 :
                                zero_padding(in, out);
                                break;
                        case 2 :
                                mirror_padding(in, out);
                                break;
                        default:
                                break;
                }
}

void Padding::zero_padding(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

	out = Eigen::VectorXd::Zero(3*this->nsamples - 2);
	memcpy(out.data() + this->nsamples - 1,in.data(),this->nsamples * sizeof(double));

}

void Padding::mirror_padding(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

	Eigen::VectorXd in_rev = in.reverse();

	memcpy(out.data(), in.data(), (this->nsamples-1) * sizeof(double));
  	memcpy(out.data() + this->nsamples - 1, in.data(), (this->nsamples-1) * sizeof(double));
  	memcpy(out.data() + 2*(this->nsamples-1), in_rev.data(), this->nsamples * sizeof(double));

}

void Padding::Unpadding(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out){


	unsigned int nchannels = in.cols();

	for (unsigned int i = 0; i < nchannels; i++) {
		memcpy(out.col(i).data(), in.col(i).data() + this->nsamples - 1, this->nsamples * sizeof(double));
	}
}



	}
}
#endif
