#ifndef PROC_HANN_HPP
#define PROC_HANN_HPP

#include "Window.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a hann window
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter and Window. It implements a hann window in time domain
 * according to the equation:
 * 
 * \f[
 *	 w(t) = 0.5 \cdot (1.0 - \frac{cos(2.0 \cdot \pi \cdot t)}{S - 1})
 * \f]
 *
 * where \f$S\f$ is the number of samples
 *
 * \sa Window
 */
class Hann : public Window {
	
	public:
		/*! \brief 	Constructor
		 *  \param 	nsamples Length of the window
		 */
		Hann(unsigned int nsamples);

		/*! \brief 	Destructor
		 */
		~Hann(void);
};
	}
}

#endif
