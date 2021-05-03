#ifndef PROC_ENVELOPE_CPP
#define PROC_ENVELOPE_CPP

#include "Envelope.hpp"

namespace wtk {
	namespace proc {

Envelope::Envelope(void) : Filter(Filter::inDomainTime) {

	this->_name 	= "envelope";

	this->_size     = 0;
	this->_isset = false;
}

Envelope::~Envelope(void) {
	fftw_free(this->_in);
	fftw_free(this->_out);
}

bool Envelope::Setup(unsigned int size) {

	this->_size = size;

	this->_in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*this->_size);
  this->_out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*this->_size);

    // Setup Hilbert method
   try {
      this->hilbert_ = new Hilbert();
      this->hilbert_->Setup(this->_size);
    } catch (std::runtime_error& e) {
      throw std::runtime_error("Can't setup Hilbert method because: '" + std::string(e.what()) + "'");
    }

	this->_isset = true;

	return this->IsSet();
}

void Envelope::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out){


	unsigned int nchannels = in.cols();

	for (unsigned int i = 0; i < nchannels; i++) {
		compute(in.col(i), out.col(i));
	}
}

void Envelope::compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

	for(unsigned int i = 0; i < this->_size; i++)
    {
      this->_in[i][REAL] = in[i];
      this->_in[i][IMAG] = 0;
    }

    this->hilbert_->Transform(this->_in , this->_out);

    std::complex<double> temp_;

    for(unsigned int i = 0; i < this->_size; i++)
    {
      //temp_.real() = this->_out[i][REAL];
      //temp_.imag() = this->_out[i][IMAG];
      temp_.real(this->_out[i][REAL]);
      temp_.imag(this->_out[i][IMAG]);

      out[i] = abs(temp_);
    }
}


bool Envelope::IsSet(void) {
	if(this->_isset == false)
		throw wtk::core::Exception("The envelope is not setup");

	return this->_isset;
}

	}
}
#endif
