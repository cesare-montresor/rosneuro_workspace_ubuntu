#ifndef PROC_HILBERT_CPP
#define PROC_HILBERT_CPP

#include "Hilbert.hpp"

namespace wtk {
	namespace proc {

Hilbert::Hilbert(void) {
	this->_isset = false;
}

Hilbert::~Hilbert(void) {
	fftw_free(this->_fft);
}

bool Hilbert::Setup(unsigned int size) {
	
	this->_size = size;

	this->_fft = (fftw_complex*) fftw_malloc(sizeof(fftw_complex)*this->_size);

  this->_isset = true;

	return this->IsSet();

}

bool Hilbert::IsSet(void) {
	if(this->_isset == false)
		throw wtk::core::Exception("The hilbert is not setup");

	return this->_isset;
}

void Hilbert::Transform(fftw_complex* in , fftw_complex* out){

  	std::complex<double> imag_neg(0 , -1);
  	std::complex<double> complex_fft(0,0);

  	fft(in, this->_fft, this->_size);

  	for(unsigned int i = 0; i < this->_size; i++)
  	{
    	//complex_fft.real() = this->_fft[i][REAL];
    	//complex_fft.imag() = this->_fft[i][IMAG];
    	complex_fft.real(this->_fft[i][REAL]);
    	complex_fft.imag(this->_fft[i][IMAG]);

    	// cast double since complex is type double
    	this->_sign = ( sign((this->_size/2) - i ));
    	this->_sign = this->_sign * sign(i);
    	complex_fft = complex_fft * imag_neg;
    	complex_fft = complex_fft * (double)this->_sign;

    	this->_fft[i][REAL] = complex_fft.real();
    	this->_fft[i][IMAG] = complex_fft.imag();
  	}

  	inverse_fft(this->_fft, out, this->_size);

  	for(unsigned int i = 0; i < this->_size; i++)
  	{
    	out[i][IMAG] = out[i][REAL];
    	out[i][REAL] = in[i][REAL];
  	}

}

void Hilbert::fft(fftw_complex* in , fftw_complex* out , unsigned int n)
{
  fftw_plan my_plan = fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

  fftw_execute(my_plan);
  fftw_destroy_plan(my_plan);
}

void Hilbert::inverse_fft(fftw_complex* in , fftw_complex* out , unsigned int n)
{
  fftw_plan my_plan = fftw_plan_dft_1d(n, in, out, FFTW_BACKWARD,
                                       FFTW_ESTIMATE);

  fftw_execute(my_plan);
  fftw_destroy_plan(my_plan);

  for(unsigned int i = 0; i < n; i++)
  {
    out[i][REAL] /= n;
    out[i][IMAG] /= n;
  }
}

int Hilbert::sign(int i)
{
  if( i == 0 )
  {
    return 0;
  }

  i > 0 ? i = 1 : i = -1;
  return i;

}

	}
}
#endif
