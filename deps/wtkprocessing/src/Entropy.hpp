#ifndef PROC_ENTROPY_HPP
#define PROC_ENTROPY_HPP

#include <eigen3/Eigen/Dense>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <wtkcore/Exception.hpp>

#include "Method.hpp"
#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements the entropy extimation of signals matrix data
 *
 * \ingroup bcitk_methods
 *
 * This class derives from Methods. It implements an entropy estimation of one
 * or multiple signals according to the classic definition of shannon Entropy:
 * 
 * \f[
 *	 H_{X} = -\sum_{i = 1}^{n} P(x_i) \log_{b}P(x_{i})
 * \f]
 *
 * where \f$H_{t}\f$ is the entropy of the signal and \f$P(x_i)\f$ is the
 * probability that the \f$x_{i}\f$ sample of X can assume that value.
 *
 * The object stores the number of bins used for the signal values distribution
 * and the respective distribution used for the entropy estimation.
 *
 * \sa Methods
 */

class Entropy : public Method {

  public:
    /*! \brief	Constructor.
     *  \param	num_bins number of bins used for the entropy evaluation
     */
    Entropy(void);
		
		/*! \brief 	Destructor 
		 */
    ~Entropy(void);

    /*! \brief 	 Setup
     *  \param num_bins the new value to be stored
		 */
    bool Setup(unsigned int num_bins);

		/*! \brief 	Implementation of the main method. It applies
     * 		the entropy algorithm.
     *  \param in 	Input signal matrix
     *  \param out	not used
		 */
    int Apply(const Eigen::Ref<const Eigen::MatrixXd>& in);


    bool IsSet();

    bool IsApplied();

    void Get(Eigen::Ref<Eigen::VectorXd> out);

    void Get(Eigen::Ref<Eigen::VectorXd> out, Eigen::Ref<Eigen::MatrixXd> distribution_binned);

    void Get(Eigen::Ref<Eigen::VectorXd> out, Eigen::Ref<Eigen::MatrixXd> distribution_binned,
             Eigen::Ref<Eigen::MatrixXd> centers_distribution);

    void Dump(void);
		
	private:

    /*! \brief 	Private method for computing entropy (single
     * 		channel)
     */
    void Compute(const Eigen::Ref<const Eigen::VectorXd>& in, double& out,
                 Eigen::Ref<Eigen::VectorXd> distribution_binned,
                 Eigen::Ref<Eigen::VectorXd> centers_distribution);

  public:
    /*! \brief Eigen flag to keep the memory block of the matrix
     * aligned
     */
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  private:

    Eigen::VectorXd entropy_;
    Eigen::MatrixXd distribution_binned_;
    Eigen::MatrixXd centers_distribution_;

    unsigned int 	num_bins_;

    bool isset_;
    bool isapplied_;


};
	}
}

#endif
