#ifndef PROC_QDA_HPP
#define PROC_QDA_HPP

#include <Eigen/Dense>
#include "Classifier.hpp"
#include "bcitk_utilities.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a qda classifier
 *
 * \ingroup bcitk_classifiers
 *
 * This class derives from Classifier. 
 * \todo Implementation of qda classifier
 * \sa Classifier
 */


class Qda : public Classifier {

	public:
		Qda(unsigned int nclasses, unsigned int nfeatures);
		~Qda(void);
		void Run(const Ref<const VectorXd>& features, Ref<Vector2d> pp);
		void Load(std::string filename);

		// To be implemented when train method is ready
		int Save(std::string filename);

	private:
		MatrixXd _centers;
		MatrixXd _covariances;
		
		unsigned int _nclasses;
		unsigned int _nfeatures;

};
	}
}

#endif
