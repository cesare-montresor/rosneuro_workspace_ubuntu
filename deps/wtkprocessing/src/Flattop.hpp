#ifndef PROC_FLATTOP_HPP
#define PROC_FLATTOP_HPP

#include "Window.hpp"

/** @name 
 * Flattop parameters
 */ 
///@{
#define BCITK_WIN_FLTP_A0	0.21557895
#define BCITK_WIN_FLTP_A1	0.41663158
#define BCITK_WIN_FLTP_A2	0.277263158
#define BCITK_WIN_FLTP_A3	0.083578947
#define BCITK_WIN_FLTP_A4	0.006947368
///@}

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
 *	 w(t) = a0 - a1 \cdot \frac{cos(2.0 \cdot \pi \cdot t)}{S - 1} + a2 \cdot \frac{cos(4.0 \cdot \pi \cdot t)}{S - 1} - a3 \cdot \frac{cos(6.0 \cdot \pi \cdot t)}{S - 1} + a4 \cdot \frac{cos(8.0 \cdot \pi \cdot t)}{S - 1}
 *
 * \f]
 *
 * where \f$S\f$ is the number of samples
 *
 * \sa Window
 */


class Flattop : public Window {
	
	public:	
		/*! \brief 	Constructor
		 *  \param 	nsamples Length of the window
		 */
		Flattop(unsigned int nsamples);
		
		/*! \brief 	Destructor
		 */
		~Flattop(void);

	public:
		/** @name 
		 * Flattop parameters
		 */ 
		///@{
		double a0;
    		double a1;
    		double a2;
    		double a3;
    		double a4;		
		///@}
};
	}
}

#endif
