#ifndef PROC_BUTTERFILTER_HPP
#define PROC_BUTTERFILTER_HPP

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <fftw3.h>
#include <iostream>
#include "Butterworth.hpp"

#include <wtkcore/Exception.hpp>

#include "Filter.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a Butterworth filter in time domain
 *
 * \ingroup bcitk_filters
 *
 *
 * The input and output data are in the format [samples x channels].
 * \sa Filter
 */

        typedef struct {
            unsigned int 		ftype;
            int 		        order;
            double              fs;
            double              fcutoff1;
            double              fcutoff2;
            int                 stride;
        } butterconfig_t;

        typedef struct {
            int                 nfilters;
            vector <Biquad>     coeffs;
            double              overallGain;
        } filterconfig_t;

class ButterFilter : public Filter {
	
	public:
		/*! \brief	Constructor.
		 */
                ButterFilter(void);
		
		/*! \brief	Destructor.
		 */
                ~ButterFilter(void);

                /*! \brief 	Setup of the main method.
                 *  Defines the filter type (LowPass, High Pass, Band Pass, Notch)
                 *  Defines the filter order
                 *  Defines the cut-off frequencies
                 */

                bool Setup(unsigned int ftype, int order, double fs, double fcutoff1, double fcutoff2);
                bool Setup(unsigned int ftype, int order, double fs, double fcutoff1);
                void Dump(void);

		/*! \brief 	Implementation of the main method. It applies
                 * 		the Butterworth filter.
		 *  \param in 	Input data matrix
		 *  \param out	Output data matrix
		 */
		virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);

                bool IsSet();

        private:
                void compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);

        public:
                butterconfig_t 	config;
                filterconfig_t  fconfig;

        private:
                bool                _isset;
                BiquadChain*        biquadchain_;
                
};
	}
}

#endif
