#ifndef PROC_BLACKMAN_HPP
#define PROC_BLACKMAN_HPP

#include "Window.hpp"

namespace wtk {
	namespace proc {


/*! \brief This class implements a hamming window
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter and Window. It implements a hamming window in time domain
 * according to the equation:
 * 
 * \f[
 *	 w(t) = \frac{1}{100.0}(42.0 - 50.0 \cdot \frac{cos(2.0 \cdot \pi \cdot t)}{S - 1} + 8.0 \cdot \frac{cos(4.0 \cdot \pi \cdot t)}{S - 1})
 * \f]
 *
 * where \f$S\f$ is the number of samples
 *
 * \sa Window
 */

class Blackman : public Window {
	
	public:
		/*! \brief 	Constructor
		 *  \param 	nsamples Length of the window
		 */
		Blackman(unsigned int nsamples);
		
		/*! \brief 	Destructor
		 */
		~Blackman(void);

};

	}
}

#endif
