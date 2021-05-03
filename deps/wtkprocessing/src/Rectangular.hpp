#ifndef RECTANGULAR_H
#define RECTANGULAR_H

#include "Window.hpp"

namespace wtk {
    namespace proc {

/*! \brief This class implements a rectangular window
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter and Window. It implements a rectangular window in time domain
 * according to the equation:
 *
 * \f[
 *	 w(t) = ones(t)
 * \f]
 *
 * where \f$ones(t)\f$ is a vector of ones of length of t multiplied for the sample rate
 *
 * \sa Window
 */
class Rectangular : public Window {

    public:
        /*! \brief 	Constructor
         *  \param 	nsamples Length of the window
         */
        Rectangular(unsigned int nsamples);

        /*! \brief 	Destructor
         */
        ~Rectangular(void);
};
    }
}


#endif // RECTANGULAR_H
