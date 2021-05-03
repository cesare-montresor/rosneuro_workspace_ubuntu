#ifndef PROC_ENVELOPE_HPP
#define PROC_ENVELOPE_HPP

#include <eigen3/Eigen/Dense>
#include <complex>
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>

#include <wtkcore/Exception.hpp>

#include "Filter.hpp"
#include "Hilbert.hpp"
#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {

class Envelope : public Filter {
	
	public:
		Envelope(void);
		
		/*! \brief	Destructor.
		 */
		~Envelope(void);
		
		/*! \brief	Setup.
		 */
		bool Setup(unsigned int size);
		
		virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);

		virtual bool IsSet(void);

	private:
		void compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);
	
	public:
		unsigned int _size;
	protected:
		bool _isset;
	private:
		fftw_complex* _in;
		fftw_complex* _out;

		Hilbert* hilbert_;

};
	}
}

#endif
