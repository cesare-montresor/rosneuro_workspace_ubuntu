#ifndef PROC_FILTER_HPP
#define PROC_FILTER_HPP

#include <string>
#include <eigen3/Eigen/Dense>


namespace wtk {
	namespace proc {

/*! \brief Pure virtual class for generic filters.
 *
 * \ingroup bcitk_filters
 *
 * This class is used to instanciate generic filters for data. As default, there
 * are four different filter types (domains): generic, spatial, time and
 * frequency.  Data is represented by a 2D matrix and it is always in the format
 * [samples x channels].  This is a pure virtual class, it can be instanciated
 * only as derived class.  \sa Car, Dc, Laplacian, Window
 */

class Filter {

	public:
		/*! \brief	Constructor
		 *  \param	domain	filter domain
		 */
		Filter(int domain);
		
		/*! \brief 	Destructor 
		 */
		~Filter(void);

		/*! \brief 	Get filter domain
		 *  \return 	The domain of the filter
		 */
		virtual int GetDomain(void);

		/*! \brief 	Get filter domain name
		 *  \return 	The name of the domain
		 */
		virtual std::string GetDomainName(void);

		/*! \brief 	Set filter name
		 *  \param 	name	The name of the filter
		 */
		virtual void SetName(std::string name);

		/*! \brief	Get filter name
		 *  \return	The current name of the filter
		 */
		virtual std::string GetName(void);

		/*! \brief 	Virtual method to apply the filter
		 * 		to the data
		 *  \param in 	Input data
		 *  \param out  Output data
		 */
		virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out) = 0;

	public:
		/** @name 
		 * Operational domains for the filters
		 */ 
		///@{
		const static int inDomainGeneric   = 0;
		const static int inDomainSpatial   = 1;
		const static int inDomainTime 	   = 2;
		const static int inDomainFrequency = 3;
		///@}
	
	private:
		/*! \brief Filter domain
		 */
		int _domain;

	protected:
		/*! \brief Filter name
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
