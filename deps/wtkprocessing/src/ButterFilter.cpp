#ifndef PROC_BUTTER_CPP
#define PROC_BUTTER_CPP

#include "ButterFilter.hpp"

using namespace std;

namespace wtk {
	namespace proc {

ButterFilter::ButterFilter(void) : Filter(Filter::inDomainTime) {
        this->_name = "butterworth";
}
ButterFilter::~ButterFilter(void) {}

bool ButterFilter::Setup(unsigned int ftype, int order, double fs, double fcutoff1, double fcutoff2) {

        try {
                // Configure Butterworth filter parameters
                this->config.ftype              = ftype;
                this->config.order              = order;
                this->config.fs                 = fs;
                this->config.fcutoff1           = fcutoff1;
                this->config.fcutoff2           = fcutoff2;

                this->config.stride             = 1;


                Butterworth butterworth;

                bool designedCorrectly = false;

                // Configure filter class
                switch(this->config.ftype) {
                        case 1 :
                                designedCorrectly = butterworth.loPass(this->config.fs,
                                                                       this->config.fcutoff1,
                                                                       this->config.fcutoff2,
                                                                       this->config.order,
                                                                       this->fconfig.coeffs,
                                                                       this->fconfig.overallGain);
                                break;
                        case 2 :
                                designedCorrectly = butterworth.hiPass(this->config.fs,
                                                                       this->config.fcutoff1,
                                                                       this->config.fcutoff2,
                                                                       this->config.order,
                                                                       this->fconfig.coeffs,
                                                                       this->fconfig.overallGain);
                                break;
                        case 3 :
                                designedCorrectly = butterworth.bandPass(this->config.fs,
                                                                         this->config.fcutoff1,
                                                                         this->config.fcutoff2,
                                                                         this->config.order,
                                                                         this->fconfig.coeffs,
                                                                         this->fconfig.overallGain);
                                break;
                        case 4 :
                                designedCorrectly = butterworth.bandStop(this->config.fs,
                                                                         this->config.fcutoff1,
                                                                         this->config.fcutoff2,
                                                                         this->config.order,
                                                                         this->fconfig.coeffs,
                                                                         this->fconfig.overallGain);
                                break;
                        default:
                                break;
                }

                this->fconfig.nfilters = this->fconfig.coeffs.size();
                this->biquadchain_ = new BiquadChain();
                this->biquadchain_->resize(this->fconfig.nfilters);
                this->biquadchain_->reset();

                /*std::cout << std::endl;
                std::cout << "Biquad 1: " << this->coeffs[0].b0 << "  " << this->coeffs[0].b1 << "  " << this->coeffs[0].b2 << "  " << this->coeffs[0].a1 << "  " << this->coeffs[0].a2 << "  " << std::endl;
                std::cout << "Biquad 2: " << this->coeffs[1].b0 << "  " << this->coeffs[1].b1 << "  " << this->coeffs[1].b2 << "  " << this->coeffs[1].a1 << "  " << this->coeffs[1].a2 << "  " << std::endl;
                std::cout << "Biquad 3: " << this->coeffs[2].b0 << "  " << this->coeffs[2].b1 << "  " << this->coeffs[2].b2 << "  " << this->coeffs[2].a1 << "  " << this->coeffs[2].a2 << "  " << std::endl;
                std::cout << "Biquad 4: " << this->coeffs[3].b0 << "  " << this->coeffs[3].b1 << "  " << this->coeffs[3].b2 << "  " << this->coeffs[3].a1 << "  " << this->coeffs[3].a2 << "  " << std::endl;

                std::cout << std::endl << "overallGain: " << this->config.overallGain << std::endl << std::endl;*/


                if (designedCorrectly){
                    this->_isset = true;
                }

        } catch (wtk::core::Exception& e) {
                printf("%s\n", e.Info().c_str());
        }

        return this->IsSet();

}

bool ButterFilter::Setup(unsigned int ftype, int order, double fs, double fcutoff1) {

        try {
                // Configure Butterworth filter parameters
                this->config.ftype              = ftype;
                this->config.order              = order;
                this->config.fs                 = fs;
                this->config.fcutoff1           = fcutoff1;
                this->config.fcutoff2           = 0;

                this->config.stride             = 1;


                Butterworth butterworth;

                bool designedCorrectly = false;

                // Configure filter class
                switch(this->config.ftype) {
                        case 1 :
                                designedCorrectly = butterworth.loPass(this->config.fs,
                                                                       this->config.fcutoff1,
                                                                       this->config.fcutoff2,
                                                                       this->config.order,
                                                                       this->fconfig.coeffs,
                                                                       this->fconfig.overallGain);
                                break;
                        case 2 :
                                designedCorrectly = butterworth.hiPass(this->config.fs,
                                                                       this->config.fcutoff1,
                                                                       this->config.fcutoff2,
                                                                       this->config.order,
                                                                       this->fconfig.coeffs,
                                                                       this->fconfig.overallGain);
                                break;
                        case 3 :
                                designedCorrectly = butterworth.bandPass(this->config.fs,
                                                                         this->config.fcutoff1,
                                                                         this->config.fcutoff2,
                                                                         this->config.order,
                                                                         this->fconfig.coeffs,
                                                                         this->fconfig.overallGain);
                                break;
                        case 4 :
                                designedCorrectly = butterworth.bandStop(this->config.fs,
                                                                         this->config.fcutoff1,
                                                                         this->config.fcutoff2,
                                                                         this->config.order,
                                                                         this->fconfig.coeffs,
                                                                         this->fconfig.overallGain);
                                break;
                        default:
                                break;
                }

                this->fconfig.nfilters = this->fconfig.coeffs.size();
                this->biquadchain_ = new BiquadChain();
                this->biquadchain_->resize(this->fconfig.nfilters);
                this->biquadchain_->reset();


                if (designedCorrectly){
                    this->_isset = true;
                }

        } catch (wtk::core::Exception& e) {
                printf("%s\n", e.Info().c_str());
        }

        return this->IsSet();

}

bool ButterFilter::IsSet(void) {
        if(this->_isset == false)
                throw wtk::core::Exception("The Butter is not setup");

        return this->_isset;
}

void ButterFilter::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out) {

    unsigned int nchannels = in.cols();
    unsigned int nsamples = in.rows();

    Eigen::MatrixXd _filt = Eigen::MatrixXd::Zero(nsamples, nchannels);

    for (unsigned int i = 0; i < nchannels; i++) {
            compute(in.col(i), _filt.col(i));
    }

    out = _filt;

}

void ButterFilter::compute(const Eigen::Ref<const Eigen::VectorXd> &in, Eigen::Ref<Eigen::VectorXd> out){

    int stride = this->config.stride;
    int nsamples = in.size();
    
    Eigen::VectorXd _out1 = Eigen::VectorXd::Zero(nsamples);
    Eigen::VectorXd _out2 = Eigen::VectorXd::Zero(nsamples);

    // FIRST FILTER
    this->biquadchain_->reset();
    this->biquadchain_->processBiquadSG(in, _out1, stride, nsamples, this->fconfig.coeffs);
    _out1 = _out1 * this->fconfig.overallGain;

    // REVERSE AND SECOND FILTER
    this->biquadchain_->reset();
    this->biquadchain_->processBiquadSG(_out1.reverse(), _out2, stride, nsamples, this->fconfig.coeffs);
    _out2 = _out2 * this->fconfig.overallGain;

    // REVERSE
    out = _out2.reverse();
}

void ButterFilter::Dump() {

    try {
        this->IsSet();

        std::cout << "Butter coefficients" <<  std::endl;
        for(int i=0; i < (int)this-> fconfig.coeffs.size();i++ )
        {
            std::cout << "Biquad " << i << ": " << this-> fconfig.coeffs[i].b0 << "  " << this-> fconfig.coeffs[i].b1 << "  " << this-> fconfig.coeffs[i].b2 << "  " << this-> fconfig.coeffs[i].a1 << "  " << this-> fconfig.coeffs[i].a2 << "  " << std::endl;
        }
        std::cout << std::endl << "overallGain: " << this->fconfig.overallGain << std::endl << std::endl;

    }
    catch (wtk::core::Exception& e) {
        printf("%s\n", e.Info().c_str());
    }


}


    }
}

#endif
