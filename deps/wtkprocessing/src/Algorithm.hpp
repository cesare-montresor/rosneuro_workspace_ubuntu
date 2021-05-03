#ifndef PROC_ALGORITHM_HPP
#define PROC_ALGORITHM_HPP

#include <string>
#include <eigen3/Eigen/Dense>

namespace wtk {
	namespace proc {

/*! \brief Pure virtual class for generic algorithms for probabilities.
 *
 * \ingroup bcitk_algorithms
 *
 * This class is used to instanciate generic algotithms for probability
 * manipulation. At the moment two types of algorithms are available. 
 * This is a pure virtual class, it can be instanciated only as derived class.
 * \sa Exponential, Rejector
 */

class Algorithm {

	public:
		/*! \brief	Constructor
		 *  \param	type	Type of algorithm
		 */
		Algorithm(int type);		
		
		/*! \brief 	Destructor 
		 */
		~Algorithm(void);
		
		/*! \brief 	Get algorithm type
		 *  \return 	The type of algorithm
		 */
		virtual int  GetType(void);
		
		/*! \brief 	Set algotithm type
		 *  \param type The type of algorithm
		 */
		virtual void SetType(int type);
		
		/*! \brief 	Set algotithm name
		 *  \param name The name of algorithm
		 */
		virtual void SetName(std::string name);
		
		/*! \brief 	Get algorithm name
		 *  \return 	The name of algorithm
		 */
		virtual std::string GetName(void);

		/*! \brief 	Virtual method to apply the algotithms
		 * 		to the probability
		 *  \param in 	Input probability vector
		 *  \param out  Output probability vector
		 */
		virtual void Apply(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) = 0;
	
	public:
		/** @name 
		 * Algorithm types
		 */ 
		///@{
		const static int AsExpAccumulation	= 0;
		const static int AsRejector 		= 1;
		///@}
	private:
		/*! \brief 	Algorithm type
		 */
		unsigned int 	_type;

		/*! \brief 	Algorithm name
		 */
		std::string 		_name;
	
	public: 
		/*! \brief Eigen flag to keep the memory block of the matrix
		 * aligned
		 */
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};
	}
}
#endif
