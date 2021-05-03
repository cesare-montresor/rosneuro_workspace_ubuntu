#ifndef PROC_EXPONENTIALPD_HPP
#define PROC_EXPONENTIALPD_HPP

#include <math.h>
#include "Algorithm.hpp"
#include "Exponential.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements an exponential smoothing algorithm for probabilities
 *
 * \ingroup bcitk_algorithms
 *
 * This class derives from Algorithm. It implements an alternative exponential smoothing
 * between two set of probabilities, according to the equation:
 * 
 * \f[
 *	 ipp_{t} = \alpha \cdot ipp_{t-1} + (1.0 - \alpha) \cdot (pp_{t} - CF_{t})
 * \f]
 *
 * and
 *
 * CF_{t} = sign(pp_{t} - 0.5) \cdot [(1 - ppcontrol_{t}) \cdot 0.5 -
 *          (0.5 - (abs(pp_{t} - 0.5)] \cdot (1 - abs(ppcontrol_{t} - ppcontrol_{t-1})
 *
 * where \f$ipp_{t}\f$ are the resulting posterior probabilities, \f$\alpha\f$
 * is the smoothing parameter, \f$pp_{t-1}\f$ and \f$pp_{t}\f$ are the posterior
 * probabilities at time \f$t\f$ and \f$t-1\f$, respectively,\f$ppcontrol_{t-1}\f$ and
 * \f$ppcontrol_{t}\f$ are the posterior probabilities at time \f$t\f$ and \f$t-1\f$,
 * respectively used as integration controller with respect to the modified exponetial
 * smoothing
 *
 * The first entry of ppcontrol contains the probability of the leading class
 * (i.e.: if ppcontrol_{t}(0) equals one means control is off, CF = 0, instead
 *  if ppcontrol_{t}(0) equals zero control is max, CF = PP - [uniform_probability_distribution])
 *
 * The object stores the value of the previous posterior probabilities. The
 * previous posterior probabilities are the ones computed last time the method
 * Rejector::Apply has been called. As initial value, the previous posterior 
 * probabilities are set as uniform distribution (given the number of classes).
 *
 * \sa Algorithm
 */

class ExponentialPd : public Algorithm {

	public:	
		/*! \brief	Constructor.
		 *  \param	alpha		The smoothing parameter
		 *  \param	nclasses	Number of class (elements in the
		 *  				probability vector, default value: 2)
		 */
    ExponentialPd(double alpha, double alpha_control, unsigned int nclasses = 2);
		
		/*! \brief 	Destructor 
		 */
    ~ExponentialPd(void);

		/*! \brief 	Get alpha value
		 *  \return 	Current alpha value
		 */
		double GetAlpha(void);

		/*! \brief 	 Set alpha value
		 *  \param alpha Alpha value
		 */
		void SetAlpha(double alpha);

    /*! \brief 	Get control probability alpha value
     *  \return 	Current alpha value
     */
    double GetControlAlpha(void);

    /*! \brief 	 Set control probability alpha value
     *  \param alpha Alpha value
     */
    void SetControlAlpha(double alpha_control);


		/*! \brief 	Get number of classes
		 *  \return	Current number of classes
		 */
		unsigned int GetNumClasses(void);

		/*! \brief 	Set number of classes
		 *  \param nclasses Number of classes
		 */
		void SetNumClasses(unsigned int nclasses);

		/*! \brief 	Method to reset the previous probabilities to
		 * 		the unifor distribution values (given the number of classes)
		 */
		void Reset(void);

    /*! \brief 	Implementation of the Exponential classic method. It applies
		 * 		the exponential algorithm.
		 *  \param in 	Input probability vector
		 *  \param out	Output probility vector
		 */
		void Apply(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);

    /*! \brief 	Implementation of the main method. It applies
     * 		the alternative exponential algorithm.
     *  \param in           Input probability vector
     *  \param in_control 	Input control probability vector
     *  \param out          Output probility vector
     */
    void ApplyPd(const Eigen::Ref<const Eigen::VectorXd>& in,
                      const Eigen::Ref<const Eigen::VectorXd>& in_control,
                      Eigen::Ref<Eigen::VectorXd> out,
                      Eigen::Ref<Eigen::VectorXd> out_control);
	private:

		/*! \brief 	Current value of alpha smoothing parameter
		 */
		double 		_alpha;

		/*! \brief 	Current number of classes
		 */
		unsigned int 	_nclasses;

		/*! \brief 	Value for the unifor distribution
		 */
		double		_udist;
		
		/*! \brief 	Probability vector with the previous
		 * 		values
		 */
		Eigen::VectorXd 	_prevprobs;

    /*! \brief 	Probability vector with the previous
     * 		control values
     */
    Eigen::VectorXd 	_prevcontrolprobs;

    /*! \brief 	Exponential smoother for the control probabilities used in ExponentialPD
     */
    Exponential 	control_exponential_ = Exponential(0 ,0);
};
	}
}

#endif
