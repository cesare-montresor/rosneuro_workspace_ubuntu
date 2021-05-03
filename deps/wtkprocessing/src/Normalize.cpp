#ifndef PROC_NORMALIZE_CPP
#define PROC_NORMALIZE_CPP

#include "Normalize.hpp"

namespace wtk {
  namespace proc {


  Normalize::Normalize(void) {
    this->_isset = false;
  }

  Normalize::~Normalize(void) {  }



bool Normalize::Setup(unsigned int ntype, unsigned int nnorm) {

    try {
            // Configure Normalization parameters
            this->config.ntype = ntype;
            this->config.nnorm = nnorm;
            this->_norm = Eigen::MatrixXd::Zero(this->config.nnorm, 1);

            switch (this->config.ntype) {
            case 1 :
                this->config.nname = "minmax";
                this->_isset = true;
                break;
            case 2 :
                this->config.nname = "z-score";
                this->_isset = true;
                break;
            default :
                break;
        }

    }
    catch (wtk::core::Exception& e) {
      printf("%s\n", e.Info().c_str());
   }
   return this->IsSet();


}

bool Normalize::IsSet(void) {
        if(this->_isset == false)
                throw wtk::core::Exception("The windsor is not setup");

        return this->_isset;
}



int Normalize::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in){

        unsigned int nchannels = in.cols();
        this->_norm.resize(Eigen::NoChange, in.cols()); // The resize should happen just the first time

        for (unsigned int i = 0; i < nchannels; i++) {
                compute(in.col(i), this->_norm.col(i));
        }

	return 0;
}



void Normalize::Dump(void) {
        printf("[normalize] - Normalization configuration:\n");
        printf("         | - Normalization type: 	%s\n", this->config.nname.c_str());

}

void Normalize::compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

    //unsigned int nsamples   = in.size();

    Eigen::VectorXd normin = in;
    Eigen::VectorXd onesVector = Eigen::VectorXd::Ones(in.size());

    switch (this->config.ntype) {
        case 1 :
            float min;
            float max;

            min = in.minCoeff();
            max = in.maxCoeff();

            normin -= onesVector * min;
            normin /= (max - min);
            normin *= 2;
            normin -= onesVector;
            break;
        case 2 :
            float mean;
            float sd;

            mean = in.mean();
            sd = getStandardDeviation(in);

            normin -= onesVector * mean;
            normin /= sd;
            break;
        default :
            break;
    }

    out = normin;

}

void Normalize::Get(Eigen::Ref<Eigen::MatrixXd> out) {

  out = this->_norm;
}

float Normalize::getStandardDeviation(const Eigen::Ref<const Eigen::VectorXd>& in) {

    unsigned int nsamples   = in.size();

    float mean;
    mean = in.mean();

    float out_sd;

    float var = 0;
    for (unsigned int i = 0; i < nsamples; i++)
    {
        var += (in[i] - mean) * (in[i] - mean);
    }
    var /= nsamples-1;

    out_sd = sqrt(var);

    return out_sd;
}

  }
}
#endif

