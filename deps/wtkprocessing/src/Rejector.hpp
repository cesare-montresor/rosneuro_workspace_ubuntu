#ifndef PROC_REJECTOR_HPP
#define PROC_REJECTOR_HPP

#include "Algorithm.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a rejection algorithm for probabilities
 *
 * \ingroup bcitk_algorithms
 *
 * This class derives from Algorithm. The Rejector class rejects input
 * probabilities below a given value. It implements two rejection modalities:
 * 	- By keeping the previous probabilities
 * 	- By replacing the rejected probabilities with a given value
 *
 * These two modalities are defines at the instansiation level. The previous
 * probabilities are the ones computed last time the method Rejector::Apply has
 * been called. As initial value, the previous posterior 
 * probabilities are set as uniform distribution (given the number of classes).

 * \sa Algorithm
 */
class Rejector : public Algorithm {

	public:
		/*! \brief	Constructor.
		 *  \param	rejection	The rejection value
		 *  \param	nclasses	Number of class (elements in the
		 *  				probability vector, default value: 2)
		 *  \param 	modality 	Rejection modality. Default
		 *  				value: Rejector::AsReplace 
		 */
		Rejector(double rejection, unsigned int nclasses, int modality = Rejector::AsReplace);

		/*! \brief 	Destructor 
		 */
		~Rejector(void);
	
		/*! \brief 	Set rejection value
		 *  \param rejection Rejection value
		 */
		virtual void SetRejection(double rejection);
		
		/*! \brief 	Get rejection value
		 *  \return 	Current rejection value
		 */
		virtual double GetRejection(void);
		
		/*! \brief 	Set replace value. The value that will be
		 * 		replaced to the current probability if they
		 * 		are below _rejection and the modality is
		 * 		Rejector::AsReplace
		 *  \param values Values for replacement
		 */
		virtual void SetValues(const Eigen::Ref<const Eigen::VectorXd>& values);

		/*! \brief	Get replacement values.
		 *  \return 	Current values for replacement
		 */
		virtual void GetValues(Eigen::Ref<Eigen::VectorXd> values);

		/*! \brief 	Set modality
		 *  \param modality Modality type
		 */
		virtual void SetModality(int modality);

		/*! \brief 	Get modality
		 *  \return 	Current modality type
		 */
		virtual int GetModality(void);

		/*! \brief 	Reset the replacement value to the uniform
		 * 		distribution (given the number of classes)
		 */
		virtual void Reset(void);

		/*! \brief 	Implementation of the main method. It applies
		 * 		the rejection algorithm.
		 *  \param in 	Input probability vector
		 *  \param out 	Output probability vector
		 */
		void Apply(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);

	public:
		/** @name 
		 * Modality of rejection
		 */ 
		///@{
		const static int AsRecursive = 1;
		const static int AsReplace   = 2;
		///@}

	private:
		/*! \brief 	Current rejection value
		 */
		double 		_rejection;

		/*! \brief 	Current rejection modality
		 */
		int    		_modality;
		
		/*! \brief 	Current number of classes
		 */
		unsigned int 	_nclasses;

		/*! \brief 	Current replacement values
		 */
		Eigen::VectorXd _values;

		/*! \brief 	Previous probability value
		 */
		Eigen::VectorXd _pvalues;
};
	}
}

#endif
