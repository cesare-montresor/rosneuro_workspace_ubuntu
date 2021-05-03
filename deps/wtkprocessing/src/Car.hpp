#ifndef PROC_CAR_HPP
#define PROC_CAR_HPP

#include "Filter.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a car filter in spatial domain
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter. It implements a car filter in spatial domain
 * according to the equation:
 * 
 * \f[
 *	 out(t) = in(t) - \frac{1}{N}\sum_{ch=1}^{N}in_{ch}(t)
 * \f]
 *
 * where \f$out(t)\f$ is the resulting filtered data at time \f$t\f$,
 * \f$in(t)\f$ is the input data at time \f$t\f$, \f$N\f$ is the number of
 * channels and \f$in_{ch}(t)\f$ is the data for channel \f$ch\f$ at time
 * \f$t\f$.  In other words, for each sample, the filter removes the common
 * component (computed by averaging all channels) from each channel.
 *
 * The input and output data are in the format [samples x channels].
 * \sa Filter
 */

class Car : public Filter {
	
	public:
		/*! \brief	Constructor.
		 */
		Car(void);
		
		/*! \brief	Destructor.
		 */
		~Car(void);

		/*! \brief 	Implementation of the main method. It applies
		 * 		the car filter.
		 *  \param in 	Input data matrix
		 *  \param out	Output data matrix
		 */
		virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);
};
	}
}

#endif
