#ifndef PROC_HILBERT_HPP
#define PROC_HILBERTH_HPP

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <complex>
#include <cmath>
#include <Eigen/Dense>
#include <fftw3.h>

#include <wtkcore/Exception.hpp>

//#include "Method.hpp"
#include "proc_utilities.hpp"

#define REAL 0
#define IMAG 1

namespace wtk {
	namespace proc {
/*! \brief This class implements hilbert method
 */

//class Hilbert : public Method {
class Hilbert {

	public:
		/*! \brief		TO CHANGE. Constructor.
		 */
		Hilbert(void);

		/*! \brief 		Destructor
		 */
		virtual ~Hilbert(void);
		
		bool Setup(unsigned int size);

		void Transform(fftw_complex* in , fftw_complex* out);

		bool IsSet();

	private:

		void fft(fftw_complex* in , fftw_complex* out , unsigned int n);
		void inverse_fft(fftw_complex* in , fftw_complex* out , unsigned int n);

		int sign(int i);

	private:

		unsigned int _size;

		fftw_complex* _fft;

		int _sign;

		bool 		_isset;

};
	}
}

#endif
