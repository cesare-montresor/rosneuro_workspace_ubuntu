#ifndef PROC_HAMMING_HPP
#define PROC_HAMMING_HPP

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
 *	 w(t) = \frac{1}{100.0}(54.0 - 46.0 \cdot \frac{cos(2.0 \cdot \pi \cdot t)}{S - 1})
 * \f]
 *
 * where \f$S\f$ is the number of samples
 
 * \sa Window
 */

class Hamming : public Window {
	
	public:	
		/*! \brief 	Constructor
		 *  \param 	nsamples Length of the window
		 */
		Hamming(unsigned int nsamples);
		
		/*! \brief 	Destructor
		 */
		~Hamming(void);
};
	}
}

#endif
