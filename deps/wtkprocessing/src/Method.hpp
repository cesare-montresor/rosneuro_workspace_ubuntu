#ifndef PROC_METHOD_HPP
#define PROC_METHOD_HPP

#include <string>
#include <eigen3/Eigen/Dense>

namespace wtk {
	namespace proc {

/*! \brief Pure virtual class for generic methods.
 *
 * \ingroup bcitk_methods
 *
 * This class is used to instanciate generic methods for data. 
 * Data is represented by a 2D matrix and it is always in the format
 * [samples x channels].  This is a pure virtual class, it can be instanciated
 * only as derived class.  
 * \sa Pwelch
 */

class Method {

	public:
		/*! \brief	Constructor
		 */
		Method(void);
		
		/*! \brief	Destructor
		 */
		~Method(void);	

		/*! \brief	Set method name
		 *  \param name	Name of the method
		 */
		virtual void SetName(std::string name);
		
		/*! \brief	Get method name
		 *  \return	Name of the method
		 */
		virtual std::string GetName(void);

		/*! \brief 	Virtual method to apply the filter
		 * 		to the data
		 *  \param in 	Input data
		 *  \param out  Output data
		 */
		virtual int Apply(const Eigen::Ref<const Eigen::MatrixXd>& in) = 0;

	private:
		/*! \brief	Name of the method
		 */
		std::string _name;

	public: 
		/*! \brief Eigen flag to keep the memory block of the matrix
		 * aligned
		 */
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};
	}
}

#endif
