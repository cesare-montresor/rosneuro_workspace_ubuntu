#ifndef GAUSSIAN_HPP
#define GAUSSIAN_HPP

#include <iostream>
#include <fstream>
#include <iomanip> 
#include <vector>
#include <Eigen/Dense>

#include <wtkcore/Exception.hpp>
#include "Classifier.hpp"
#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a gaussian classifier
 *
 * \ingroup bcitk_classifiers
 *
 * This class derives from Classifier. It implements a Gaussian classifier
 * according to [Millán, J. d. R., Renkens, F., Mouriño, J., & Gerstner, W. 
 * (2004). Brain-actuated interaction. Artificial Intelligence, 159(1-2), 241–59].
 *
 * The object store all the parameters needed for implementing the gaussian
 * classification such as number of classes, number of prototype and number of
 * features.
 *
 * \sa Classifier
 */

typedef struct {

	std::string 		filename;

	std::string		subject;
	uint32_t		nclasses;
	std::vector<uint32_t> 	classlbs;
	uint32_t		nprototypes;
	uint32_t		nfeatures;
	char			sharedcov;
	float 			mimean;
	float 			micov;
	
	std::vector<uint32_t> 	idchan;
	std::vector<uint32_t> 	idfreq;

} gauconfig_t;


class Gaussian : public Classifier {

	public:
		Gaussian(void);
		~Gaussian(void);
		
		bool Setup(std::string filename);

		bool Setup(gauconfig_t* config, const Eigen::Ref<const Eigen::MatrixXd>& centers, const Eigen::Ref<const Eigen::MatrixXd>& covs);

		bool IsSet(void);

		void Run(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);

		bool Export(std::string filename, std::ios::openmode mode = std::ios::binary);
		
		void Dump(void);

	public:
		gauconfig_t 	config;
		Eigen::MatrixXd centers;
		Eigen::MatrixXd covs;

	private:
		bool 		_isset;
		std::string 	_stype;
		std::string 	_slabel;
		

};
	}
}


#endif
