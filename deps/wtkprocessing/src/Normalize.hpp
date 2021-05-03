#ifndef PROC_NORMALIZE_HPP
#define PROC_NORMALIZE_HPP

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <iostream>
#include <algorithm>

#include <wtkcore/Exception.hpp>

#include "Method.hpp"
#include "proc_utilities.hpp"

namespace wtk {
        namespace proc {

        typedef struct {
                unsigned int 		ntype;
                std::string             nname;
                unsigned int nnorm;

        } normalizeconfig_t;

        class Normalize : public Method {

                public:
                        /*! \brief		TO CHANGE. Constructor.
                         */
                        Normalize(void);

                        /*! \brief 		Destructor
                         */
                        virtual ~Normalize(void);

                        bool Setup(unsigned int, unsigned int);

                        /*! \brief 	Implementation of the main method. It applies
                         * 		the normalization on the input data for each channel.
                         *  \param in 	Input data matrix
                         *  \param out	Output data matrix
                         */

                        void Get(Eigen::Ref<Eigen::MatrixXd> out);

                        int Apply(const Eigen::Ref<const Eigen::MatrixXd>& );
                        bool IsSet();

                        /*! \brief 		Dump normalize information
                         */
                        void Dump(void);
                private:

                        /*! \brief 	Private method for computing normalization (single
                         * 		channel)
                         */
                        void compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);

                        float getStandardDeviation(const Eigen::Ref<const Eigen::VectorXd>& in);

                public:
                        normalizeconfig_t 	config;

                private:

                        bool 		_isset;
                        Eigen::MatrixXd _norm;

                public:
                        /*! \brief Eigen flag to keep the memory block of the matrix
                         * aligned
                         */
                        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        };

        }
}


#endif // PROC_NORMALIZE_HPP
