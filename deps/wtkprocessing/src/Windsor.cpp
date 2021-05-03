#ifndef PROC_WINDSOR_CPP
#define PROC_WINDSOR_CPP

#include "Windsor.hpp"



namespace wtk {
  namespace proc {



  Windsor::Windsor(void) {
    this->_isset = false;
  }

  Windsor::~Windsor(void) {  }

  bool Windsor::Setup(Eigen::VectorXd l_limit, Eigen::VectorXd u_limit, unsigned int nwind) {

    try {
            // Configure Windsor parameters
            //this->config.perc = perc;
            this->config.l_limit = l_limit;
            this->config.u_limit = u_limit;
            this->config.nwind = nwind;
            this->_isset = true;
            this->_wind = Eigen::MatrixXd::Zero(this->config.nwind, 1);
    }
    catch (wtk::core::Exception& e) {
        printf("%s\n", e.Info().c_str());
     }

   /* for(int i=0; i<config.l_limit.rows();i++)
    {
        std::cout << this->config.l_limit[i] << "\n ";
    }
    return this->IsSet();  */

	return true;

}


bool Windsor::IsSet(void) {
        if(this->_isset == false)
                throw wtk::core::Exception("The windsor is not setup");

        return this->_isset;
}


void Windsor::compute(const Eigen::Ref<const Eigen::VectorXd>& in, const unsigned int channel, Eigen::Ref<Eigen::VectorXd> out) {
    unsigned int nsamples   = in.size();
    //float perc = this->config.perc; /no

    //unsigned int nclip = round(nsamples*perc/2);

    //Eigen::VectorXd sortin = in;
    Eigen::VectorXd tempin = in;

    //std::sort (sortin.data(), sortin.data() + sortin.size()); /No

    //float l_limit = sortin[nclip-1]; no
    //float u_limit = sortin[nsamples-nclip]; /no

    for (unsigned int i = 0; i < nsamples; i++)
    {
        if (tempin[i] <  this->config.l_limit[channel]) {
            tempin[i] =  this->config.l_limit[channel];
        }
        else if (tempin[i] >  this->config.u_limit[channel]) {
            tempin[i] = this->config.u_limit[channel];
        }
        else {
            tempin[i] = tempin[i];
        }
    }

    out = tempin;
  }


int Windsor::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in){

        unsigned int nchannels = in.cols();
        this->_wind.resize(Eigen::NoChange, in.cols()); // The resize should happen just the first time

        for (unsigned int i = 0; i < nchannels; i++) {
               compute(in.col(i), i, this->_wind.col(i));
        }

		return 0;

}


void Windsor::Get(Eigen::Ref<Eigen::MatrixXd> out) {

  out = this->_wind;
}

void Windsor::Dump(void) {
        printf("[windsor] - Windsor configuration:\n");
        //printf("         | - Windsor percentage: 	%f\n", this->config.perc);
}


}
}
#endif

