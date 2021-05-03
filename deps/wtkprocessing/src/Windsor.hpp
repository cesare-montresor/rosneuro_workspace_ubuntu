#ifndef WINDSOR_HPP
#define WINDSOR_HPP

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
              Eigen::VectorXd 		l_limit;
              Eigen::VectorXd       u_limit;
                unsigned int nwind;
        } windsorconfig_t;

        class Windsor : public Method {

                public:
                        /*! \brief		TO CHANGE. Constructor.
                         */
                        Windsor(void);

                        /*! \brief 		Destructor
                         */
                        virtual ~Windsor(void);

                        bool Setup(Eigen::VectorXd, Eigen::VectorXd, unsigned int);

                        /*! \brief 	Implementation of the main method. It applies
                         * 		the windsor on the input data for each channel.
                         *  \param in 	Input data matrix
                         *  \param out	Output data matrix
                         */

                        int Apply(const Eigen::Ref<const Eigen::MatrixXd>& in);

                        void Get(Eigen::Ref<Eigen::MatrixXd> out);

                        bool IsSet();

                        /*! \brief 		Dump windsor information
                         */
                        void Dump(void);
                private:

                        /*! \brief 	Private method for computing windsor (single
                         * 		channel)
                         */
                        void compute(const Eigen::Ref<const Eigen::VectorXd>& in, const unsigned int channel, Eigen::Ref<Eigen::VectorXd> out);

                public:
                        windsorconfig_t 	config;


                private:

                        bool 		_isset;
                        Eigen::MatrixXd _wind;



                public:
                        /*! \brief Eigen flag to keep the memory block of the matrix
                         * aligned
                         */
                        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        };

        }
}


#endif // WINDSOR_HPP
