#ifndef PROC_DC_HPP
#define PROC_DC_HPP

#include "Filter.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a dc temporal filter in time domain
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter. It implements a dc filter in time domain
 * according to the equation:
 * 
 * \f[
 *	 out = in - \frac{1}{S}\sum_{s=1}^{s}in
 * \f]
 *
 * where \f$out\f$ is the resulting filtered data, \f$in\f$ is the input data,
 * and \f$S\f$ is the number of samples.  In other words, the filters removes
 * the DC componentd by removing the average value of signal computed on the
 * whole sample period.
 *
 * The input and output data are in the format [samples x channels].
 * \sa Filter
 */

class Dc : public Filter {
	
	public:
		/*! \brief	Constructor.
		 */
		Dc(void);

		/*! \brief	Destructor.
		 */
		~Dc(void);
		
		/*! \brief 	Implementation of the main method. It applies
		 * 		the dc filter.
		 *  \param in 	Input data matrix
		 *  \param out	Output data matrix
		 */
		 virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);
};

	}
}

#endif
