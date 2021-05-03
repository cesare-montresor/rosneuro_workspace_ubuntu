#ifndef PROC_EXPONENTIAL_HPP
#define PROC_EXPONENTIAL_HPP

#include "Algorithm.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements an exponential smoothing algorithm for probabilities
 *
 * \ingroup bcitk_algorithms
 *
 * This class derives from Algorithm. It implements an exponential smoothing
 * according to the equation:
 * 
 * \f[
 *	 ipp_{t} = \alpha \cdot pp_{t-1} + (1.0 - \alpha) \cdot pp_{t}
 * \f]
 *
 * where \f$ipp_{t}\f$ are the resulting posterior probabilities, \f$\alpha\f$
 * is the smoothing parameter, \f$pp_{t-1}\f$ and \f$pp_{t}\f$ are the posterior
 * probabilities at time \f$t\f$ and \f$t-1\f$, respectively.
 *
 * The object stores the value of the previous posterior probabilities. The
 * previous posterior probabilities are the ones computed last time the method
 * Rejector::Apply has been called. As initial value, the previous posterior 
 * probabilities are set as uniform distribution (given the number of classes).
 *
 * \sa Algorithm
 */

class Exponential : public Algorithm {

	public:	
		/*! \brief	Constructor.
		 *  \param	alpha		The smoothing parameter
		 *  \param	nclasses	Number of class (elements in the
		 *  				probability vector, default value: 2)
		 */
		Exponential(double alpha, unsigned int nclasses = 2);
		
		/*! \brief 	Destructor 
		 */
		~Exponential(void);

		/*! \brief 	Get alpha value
		 *  \return 	Current alpha value
		 */
		double GetAlpha(void);

		/*! \brief 	 Set alpha value
		 *  \param alpha Alpha value
		 */
		void SetAlpha(double alpha);

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

		/*! \brief 	Implementation of the main method. It applies
		 * 		the exponential algorithm.
		 *  \param in 	Input probability vector
		 *  \param out	Output probility vector
		 */
		void Apply(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);

		
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
};
	}
}

#endif
