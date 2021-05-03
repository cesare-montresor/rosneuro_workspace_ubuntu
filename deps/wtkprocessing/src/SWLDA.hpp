#ifndef SWLDA_HPP
#define SWLDA_HPP

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

/*! \brief This class implements a Stepwise LDA classifier
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

} swldaconfig_t;


class SWLDA : public Classifier {

        public:
                SWLDA(void);
                ~SWLDA(void);

                bool Setup(std::string filename);

                bool Setup(swldaconfig_t* config, const Eigen::Ref<const Eigen::VectorXd>& weights);

                bool IsSet(void);

                double Classify(const Eigen::Ref<const Eigen::VectorXd>& in);

                bool Export(std::string filename, std::ios::openmode mode = std::ios::binary);

                void Dump(void);

        public:
                swldaconfig_t 	config;
                Eigen::VectorXd weights;

        private:
                bool 		_isset;
                std::string 	_stype;
                std::string 	_slabel;


};
        }
}


#endif
