#ifndef BLDA_HPP
#define BLDA_HPP

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

/*! \brief This class implements a Bayesian LDA classifier
 *
 * \ingroup bcitk_classifiers
 *
 *
 * \sa Classifier
 */

typedef struct {

        std::string 		      filename;
        std::string		          subject;
        uint32_t		          nclasses;
        uint32_t		          nfeatures;
        std::vector<uint32_t> 	     classlbs;
        std::vector<uint32_t> 	     idchan;
        std::vector<uint32_t>        epochrd;
        uint32_t 	              nprob;
        Eigen::VectorXd    l_limit;
        Eigen::VectorXd     u_limit;

} bldaconfig_t;


class BLDA : public Classifier {

        public:
                BLDA(void);
                ~BLDA(void);

                bool Setup(std::string filename);

                bool Setup(bldaconfig_t* config, const Eigen::Ref<const Eigen::VectorXd>& weights,
                                                  const Eigen::Ref<const Eigen::MatrixXd>& precision, double beta);

                bool IsSet(void);

                void Run(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);
                double Classify(const Eigen::Ref<const Eigen::VectorXd>& in);

                double GetVariance(const Eigen::Ref<const Eigen::VectorXd>& in);

                bool Export(std::string filename, std::ios::openmode mode = std::ios::binary);

                void Dump(void);

        public:
                bldaconfig_t 	config;
                double beta;
                Eigen::VectorXd weights;
                Eigen::MatrixXd precision;

        private:
                bool 		_isset;
                std::string 	_stype;
                std::string 	_slabel;


};
        }
}


#endif
