#ifndef PROC_PERIODOGRAM_CPP
#define PROC_PERIODOGRAM_CPP

#include "Periodogram.hpp"

namespace wtk {
    namespace proc {

Periodogram::Periodogram(void) {
    this->_isset = false;
}

Periodogram::~Periodogram(void) {
    fftw_free(this->_plan);
    free(this->_window);
}

bool Periodogram::Setup(unsigned int wlength, unsigned int wtype, unsigned int fs, bool dolog) {

    try{
        //Configure Periodograms parameters
        this->config.wlength    = wlength;
        this->config.wtype      = wtype;
        this->config.nfft       = compute_nfft(config.wlength);
        this->config.fs         = fs;
        this->config.dolog      = dolog;
        this->config.grid       = compute_grid(config.wlength, this->config.nfft, config.fs);

        // Configure window class
        switch(this->config.wtype) {
            case Window::AsHann :
                this->_window = new Hann(this->config.wlength);
                break;
            case Window::AsHamming :
                this->_window = new Hamming(this->config.wlength);
                break;
            case Window::AsBlackman :
                this->_window = new Blackman(this->config.wlength);
                break;
            case Window::AsFlattop :
                this->_window = new Flattop(this->config.wlength);
                break;
            case Window::AsRectangular :
                this->_window = new Rectangular(this->config.wlength);
                break;
            default:
                break;
        }

        // Initialize in and out vectors for plan creation
        this->_wsig 	= Eigen::VectorXd::Zero(this->config.wlength);
        this->_wpxx 	= Eigen::VectorXd::Zero(this->config.wlength);

        // Create plan for fft
        this->_plan 	= fftw_plan_r2r_1d(this->config.wlength, this->_wsig.data(),
                                           this->_wpxx.data(), FFTW_R2HC, FFTW_PATIENT);

        if(this->_plan == NULL)
            throw wtk::core::Exception("FFTW plan not created");

        // Initialize internal psd
        this->_psd = Eigen::MatrixXd::Zero(this->config.nfft, 1);

        this->_isset = true;
    } catch (wtk::core::Exception& e) {
        printf("%s\n", e.Info().c_str());
    }

    return this->IsSet();
}

bool Periodogram::IsSet(void) {
    if(this->_isset == false)
        throw wtk::core::Exception("The periodogram is not setup");

    return this->_isset;
}

int Periodogram::Apply(const Eigen::Ref<const Eigen::MatrixXd>& in){


    //unsigned int nchannels = in.cols();

    this->_psd.resize(Eigen::NoChange, in.cols()); // The resize should happen just the first time

    for (unsigned int i = 0; i <1/*< nchannels*/; i++) {
        compute(in.col(i), this->_psd.col(i));
    }

    // Compute log norm
    if (this->config.dolog) {
        this->_psd = this->_psd.array().log();
	}

	return 0;
}

void Periodogram::Get(Eigen::Ref<Eigen::MatrixXd> out) {

    out = this->_psd;
}

void Periodogram::Get(Eigen::Ref<Eigen::MatrixXd> out, std::vector<uint32_t> freqs) {

    this->getfrequencies(out, freqs);
}

void Periodogram::Get(Eigen::Ref<Eigen::VectorXd> out, std::vector<uint32_t> idchan, std::vector<uint32_t> idfreq) {

    this->getfeatures(out, idchan, idfreq);
}


void Periodogram::Dump(void) {
    printf("[periodogram] - Periodogram configuration:\n");
    printf("         | - Window size: 	%d\n", this->config.wlength);
    printf("         | - Window type: 	%s\n", this->_window->GetWindowName().c_str());
    printf("         | - Nfft: 		%d\n", this->config.nfft);
    printf("         | - Sampling rate: 	%d\n", this->config.fs);
    printf("         | - Dolog: 		%d\n", this->config.dolog);
}



void Periodogram::compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out) {

    unsigned int wlength	= in.size();
    unsigned int nfft    	= this->config.nfft;
    unsigned int fs      	= this->config.fs;

    double wnorm		= this->_window->GetWindowNorm();
    double pxxnorm;

    Eigen::VectorXd  wsegm 	= Eigen::VectorXd::Zero(wlength);
    Eigen::VectorXd  pxx	= Eigen::VectorXd::Zero(nfft);

    unsigned int sstart = 0;

    wsegm = in.segment(sstart, wlength);
    this->_window->Apply(wsegm, this->_wsig);
    fftw_execute_r2r(this->_plan, this->_wsig.data(), this->_wpxx.data());

        // out spans from 0 to wLength/2 (NFFT = wLength/2 + 1)
        // ex. 	wLength  = n = 256
        //	NFFT          = 129 (0:1:128)
        //
        //	out(0) 	 = wpxx(0)^2 	[Only real part - Half complex vector]
        //	out(n/2) = wpxx(n/2)^2	[Only real part - wlenght is even - Half complex vector]
        //	out(k) 	 = wpxx(k)^2 + wpxx(n-k)^2, k = 1 : (n/2 - 1) [Real and imagery part]

    pxx(0) = pow(this->_wpxx(0), 2);
    pxx(wlength/2) = pow(this->_wpxx(wlength/2), 2);
    pxx.segment(1, wlength/2 - 1).array() = this->_wpxx.segment(1, wlength/2 - 1).array().pow(2)
                                    + this->_wpxx.segment(wlength/2 + 1, wlength/2 - 1).reverse().array().pow(2);

    /* NORMALIZATION FACTOR */

    pxxnorm = (wnorm * wlength * fs)/2.0;

    pxx(0) = pxx(0) / (2.0 * pxxnorm);
    pxx(wlength/2) = pxx(wlength/2) / (2.0 * pxxnorm);
    pxx.segment(1, wlength/2 - 1) = pxx.segment(1, wlength/2 - 1) / pxxnorm;

    out = pxx;
}

std::vector<uint32_t> Periodogram::compute_grid(unsigned int wlength, unsigned int nfft, unsigned int fs) {

    Eigen::VectorXi grid;
    std::vector<uint32_t> vgrid;
    unsigned int i;

	// Edited by L.Tonin  <luca.tonin@epfl.ch> on 22/07/19 10:19:08
	// Need to re-cast otherwise error in compilation

	grid = Eigen::VectorXi::LinSpaced(nfft, 0, nfft - 1) * (int)std::floor(fs/wlength);
    //grid = Eigen::VectorXi::LinSpaced(nfft, 0, nfft - 1) * floor(fs/wlength);

    for (i=0; i< grid.size(); i++)
        vgrid.push_back(grid(i));

    return vgrid;

}

unsigned int Periodogram::compute_nfft(unsigned int wlength) {
    return floor(wlength/2) + 1;
}

void Periodogram::getfrequencies(Eigen::Ref<Eigen::MatrixXd> out, std::vector<uint32_t> freqs)
{
    std::vector<uint32_t>::iterator itf;
    std::vector<uint32_t>::iterator itg;
    std::vector<uint32_t>::iterator iti;
    std::vector<uint32_t> indexes;
    unsigned int idx;

    for(itf = freqs.begin(); itf != freqs.end(); itf++) {
        idx = 0;
        for (itg = this->config.grid.begin(); itg != this->config.grid.end(); itg++) {

            if( (*itf) == (*itg) ) {
                indexes.push_back(idx);
                break;
            }
            idx++;
        }
    }

    idx = 0;
    for(iti = indexes.begin(); iti != indexes.end(); iti++) {
        out.row(idx) = this->_psd.row((*iti));
        idx++;
    }

}

void Periodogram::getfeatures(Eigen::Ref<Eigen::VectorXd> out, std::vector<uint32_t> idchan, std::vector<uint32_t> idfreq)
{
    unsigned int sizec = idchan.size();
    unsigned int sizef = idchan.size();
    unsigned int i, u, j;
    unsigned int cfreq, cchan;

    try {

        proc_check_dim(sizec, sizef, "Feature vectors have different size");


        j = 0;
        for (i = 0; i < sizec; i++) {
            for (u = 0; u < this->config.grid.size(); u++) {
                cfreq = idfreq.at(i); //Idx(i, 0);
                cchan = idchan.at(i) - 1; //Idx(i, 1) - 1;
                if (cfreq == this->config.grid.at(u)) {
                    out(j) = this->_psd(u, cchan);
                    j++;
                }
            }
        }
    } catch (wtk::core::Exception& e) {
        printf("%s\n", e.Info().c_str());
    }
}
    }
}
#endif
