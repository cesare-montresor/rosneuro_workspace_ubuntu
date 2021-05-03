#ifndef PROC_LAPLACIAN_HPP
#define PROC_LAPLACIAN_HPP

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <fstream>

#include <wtkcore/Exception.hpp>

#include "Filter.hpp"
#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a laplacian filter in spatial domain
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter. It implements a laplacian filter in spatial domain
 * according to the equation:
 * 
 * \f[
 *	 out(t) = in(t) * mask
 * \f]
 *
 * where \f$out(t)\f$ is the resulting filtered data at time \f$t\f$,
 * \f$in(t)\f$ is the input data at time \f$t\f$ and \f$mask\f$ is laplacian
 * mask with the weights layout. Input and output data are in the format S
 * samples x N channels, while the laplacian mask is a square matrix S x S.
 * At the moment, the mask is preloaded (when the object is instantiated).
 * In the next versions, the mask could be also be generated according to the
 * electrodes distances and layout.
 * \sa Filter
 */

typedef struct {
	std::string  filename;
	unsigned int size;
} lapconfig_t;

class Laplacian : public Filter {
	
	public:
		Laplacian(void);
		Laplacian(std::string filename);
		
		/*! \brief	Destructor.
		 */
		~Laplacian(void);
		
		/*! \brief	Setup.
		 *  \param ext_mask Path to external binary files with the mask
		 *  		    matrix
		 */
		bool Setup(std::string filename);

		/*! \brief	Setup.
		 *  \param ext_mask Pointer to memory where the mask is stored. 
		 *		    (e.g., pointer to array)
		 *  \param nelem    Number of channels of the mask
		 */
		bool Setup(const double* ext_mask, unsigned int nelem);
		
		/*! \brief	Setup.
		 *  \param mask Matrix with mask weights
		 */
		bool Setup(const Eigen::Ref<const Eigen::MatrixXd>& mask);

		/*! \brief 	Get laplacian mask
		 *  \param mask	The current mask
		 */
		void GetMask(Eigen::Ref<Eigen::MatrixXd> mask);

		/*! \brief 	Store new mask
		 *  \param mask  Mask to be stored
		 */
		void SetMask(const Eigen::Ref<const Eigen::MatrixXd>& mask);
	
		/*! \brief 	Implementation of the main method. It applies
		 * 		the laplacian filter.
		 *  \param in 	Input data matrix
		 *  \param out	Output data matrix
		 */
		virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);

		virtual bool IsSet(void);
	
		void Dump(void);
	
	public:
		lapconfig_t	config;
	protected:
		bool _isset;

	private:
		/*! \brief 	The mask stored
		 */
		Eigen::MatrixXd _mask;

		/*! \brief 	Pointer to the external memory block
		 */
		double * _memblock;

		std::string 	_stype;
		std::string	_slabel;

};
	}
}

#endif
