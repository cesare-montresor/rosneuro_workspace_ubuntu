#ifndef PROC_WINDOW_HPP
#define PROC_WINDOW_HPP

#include <Eigen/Dense>
#include <string>
#include "Filter.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a generic window in time domain
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter. It implements a generic window in time
 * domain. Different window are available. The input data is windowed according
 * to the type of window selected.  
 * The input and output data are in the format [samples x channels].
 * \sa Filter, Hann, Hamming, Blackman, Flattop
 */

class Window : public Filter {

	public:
		/*! \brief	Constructor
		 *  \param	wtype	Type of window
		 */
		Window(int wtype);
		
		/*! \brief 	Destructor 
		 */
		~Window(void);

		/*! \brief 	Get window type
		 *  \return 	Window type
		 */
		int GetWindowType(void);
	
		std::string GetWindowName(void);

		/*! \brief 	Get window shape
		 *  \param window Window shape
		 */
		void GetWindow(Eigen::Ref<Eigen::VectorXd> window);

		/*! \brief 	Get window norm
		 *  \return	The norm of the window
		 */
		double GetWindowNorm(void);
		
		/*! \brief 	Implementation of the main method. It applies
		 * 		the window.
		 *  \param in 	Input data matrix
		 *  \param out	Output data matrix
		 */
    virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);

	protected:
		/*! \brief 	Compute the window norm
		 *  \return 	The norm of the window computed as:
		 *  		\f$ norm = \frac{1}{S}\sum_{t=0}^{S}w^{2}(t) \f$
		 */
		double ComputeNorm(void);

	public:
		/** @name 
		 * Type of windows
		 */ 
		///@{
        const static int AsHann 	   = 1;
        const static int AsHamming 	   = 2;
        const static int AsBlackman    = 3;
        const static int AsFlattop 	   = 4;
        const static int AsRectangular = 5;
		///@}
	
	protected:
		/*! \brief	Shape of the window
		 */
		Eigen::VectorXd _window;		

		/*! \brief 	Norm of the window
		 */
		double _windownorm;

		/*! \brief 	Number of samples
		 */
		unsigned int _numsamples;

		std::string	_wname;



		
	private:
		/*! \brief 	Window type
		 */
		int _wtype;

};
	}
}

#endif
