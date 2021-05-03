#ifndef PROC_PADDING_HPP
#define PROC_PADDING_HPP

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <fftw3.h>

#include <wtkcore/Exception.hpp>

//#include "Method.hpp"
#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {
/*! \brief This class implements some padding methods
 *
 * \ingroup bcitk_methods
 *
 *
 * The input data is in the format [samples x channels].
 * The output data is in the format [(3*samples-2) x channels].
 * \sa Method
 */

//class Padding : public Method {
class Padding {

	public:

		Padding(void);

		/*! \brief 		Destructor
		 */
		virtual ~Padding(void);
		
		bool Setup(unsigned int padding_type, unsigned int n_samples);

		bool IsSet();

		void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);
		void Unpadding(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);

	private:
		void compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);
		void zero_padding(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);
		void mirror_padding(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);

	private:
		unsigned int padding_type;
		unsigned int nsamples;

		bool 		_isset;
		
};
	}
}

#endif
