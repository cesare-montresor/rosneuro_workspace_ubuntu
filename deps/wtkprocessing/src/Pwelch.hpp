#ifndef PROC_PWELCH_HPP
#define PROC_PWELCH_HPP

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <fftw3.h>

#include <wtkcore/Exception.hpp>

#include "Method.hpp"
#include "Window.hpp"
#include "Hann.hpp"
#include "Hamming.hpp"
#include "Blackman.hpp"
#include "Flattop.hpp"
#include "Rectangular.hpp"
#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {
/*! \brief This class implements pwelch method
 *
 * \ingroup bcitk_methods
 *
 * This class derives from Method. It implements a pwelch method to get power
 * spectral density from input data. The interface is inspired from the MATLAB
 * pwelch algorithm. The Fast Fourier Transform (FFT) is computed with fftw3
 * libraries (http://www.fftw.org).
 *
 * <b>FFTW3:</b>
 *
 * FFTW3 allows to create a plan at the level of instantation. Then the plan is
 * re-used as many time as needed. This saves time for computation.
 *
 * <b>Welch's method (from MATLAB):</b>
 *
 * "The method consists of dividing the time series data into (possibly
 * overlapping) segments, computing a modified periodogram of each segment, and
 * then averaging the PSD estimates. The result is Welch's PSD estimate."
 *
 * <b>Division in segments:</b>
 *
 * Input data is divided in N segments, each one of length W:
 * 
 * \f[
 * 	N = \frac{S - Novl}{W - Novl}
 * \f]
 *
 * where:
 * 	- \f$N\f$ is the resulting number of segment
 * 	- \f$S\f$ is the number of samples in the input data
 * 	- \f$W\f$ is the length of the window to be used to computed the FFT
 * 	- \f$Novl\f$ is the length of the overal between windows
 *
 * <b>Operations:</b>
 *
 * Input data is manipulated as follows:
 * 	-# For each segment, part of the data of length \f$W\f$ is extracted
 * 	-# A filter window is applied on the extracted data (by default Hamming window)
 * 	-# FFT is computed on the extracted data
 * 	-# The resulting FFT complex array is tranformed in real array (and power of 2 is applied, element-wise) 
 * 	-# The resulting FFT is averaged across segments
 * 	-# The resulting power density is normalized
 * 	-# This procedure is computed for each channel od data
 *
 * <b>From (half) complex to real array:</b>
 *
 * Given a window of length \f$W\f$ FFTW returns a complex array of length \f$W\f$, where:
 *	- \f$wpxx_{R}(0) = wpxx_{C}^{2}(0) \f$, Only real part. Half complex vector
 *	- \f$wpxx_{R}(W/2) = wpxx_{C}^{2}(W/2)\f$, Only real part. Half complex vector
 *	- \f$wpxx_{R}(k) = wpxx_{C}^{2}(k) + wpxx_{C}^{2}(n-k)\f$, where \f$ k = 1 : (W/2 - 1)\f$. Real and imagery part
 *
 * <b>NFFT:</b>
 *
 * The number of FFT points is computed according to the length of window
 * \f$W\f$ provided. <b>At the time being, only even length are supported.</b> The
 * resulting NFFT is computed as follows:
 *
 * \f[
 * 	NFFT = \frac{W}{2} + 1
 * \f]
 * 
 * <b> Frequency grid: </b>
 *
 * The spectral density is computed a pre-defined frequency values. The
 * resulting frequency grid is:
 * 	- Start: 0 Hz
 * 	- Stop: \f$NFFT - 1\f$
 * 	- Step: \f$Fs/W\f$, where \f$Fs\f$ is the sampling rate and \f$W\f$ is the lentgh of the window
 *
 * <b>Normalization:</b>
 * 
 * The resulting spectral density is normalized as follows:
 * 	- \f$pxx(0) = \frac{pxx(0)}{2 \cdot pxxnorm}\f$
 * 	- \f$pxx(W/2) = \frac{pxx(W/2)}{2 \cdot pxxnorm}\f$
 * 	- \f$pxx(k) = \frac{pxx(k)}{pxxnorm}\f$
 *
 * where \f$W\f$ is the lentgh of the window, \f$ k = 1 : (W/2 - 1)\f$ and \f$pxxnorm\f$ is:
 *
 * \f[
 * 	pxxnorm = frac{1}{2} \cdot N \cdot Wnorm \cdot Fs \cdot W
 * \f]
 *
 * with \f$N\f$ the number of segments, \f$Wnorm\f$ the window normalization
 * (see Window), \f$Fs\f$ the sampling rate and \f$W\f$ the length of the
 * window.
 *
 * <b>Logaritmic normalization:</b>
 *
 * Optionally, the resulting power spectral density can be normalized by appling
 * log operation (true by default).
 *
 * The input data is in the format [samples x channels].
 * The output data is in the format [frequency x channels].
 * \sa Method
 */

typedef struct {
	unsigned int 		wlength;
	unsigned int 		wtype;
	unsigned int 		novl;
	unsigned int 		nfft;
	unsigned int 		fs;
	bool 	   		dolog;

	std::vector<uint32_t> 	grid;
} pwelchconfig_t;

class Pwelch : public Method {

	public:
		/*! \brief		TO CHANGE. Constructor.
		 *  \param wlength 	Length of the window
		 *  \param wtype 	Window type (see Window)
		 *  \param novl		Lenght of overlap
		 *  \param fs		Sampling rate
		 *  \param dolog	Computed the log of psd (by default: true)
		 */
		Pwelch(void);

		/*! \brief 		Destructor
		 */
		virtual ~Pwelch(void);
		
		bool Setup(unsigned int wlength, unsigned int wtype, unsigned novl, unsigned int fs, bool dolog);

		/*! \brief 	Implementation of the main method. It applies
		 * 		the pwelch on the input data for each channel.
		 *  \param in 	Input data matrix
		 *  \param out	Output data matrix
		 */
		int Apply(const Eigen::Ref<const Eigen::MatrixXd>& in);

		bool IsSet();

		void Get(Eigen::Ref<Eigen::MatrixXd> out);
		void Get(Eigen::Ref<Eigen::MatrixXd> out, std::vector<uint32_t> freqs);
		void Get(Eigen::Ref<Eigen::VectorXd> out, std::vector<uint32_t> idChan, std::vector<uint32_t> idFreq);


		/*! \brief 		Dump Pwelch information
		 */
		void Dump(void);
	private:

		/*! \brief 	Private method for computing pwelch (single
		 * 		channel)
		 */
		void compute(const Eigen::Ref<const Eigen::VectorXd>& in, Eigen::Ref<Eigen::VectorXd> out);

		/*! \brief 	Private method for computing number of segments 
		 */
		unsigned int compute_nsegments(unsigned int wlength, unsigned int novl, unsigned int nsamples);

		/*! \brief 	Private method for computing frequency grid 
		 */
		std::vector<uint32_t> compute_grid(unsigned int wlength, unsigned int nfft, unsigned int fs);

		/*! \brief 	Private method for computing NNF
		 *  \todo	Implement case with odd wlength
		 */
		unsigned int compute_nfft(unsigned int wlength);

		void getfeatures(Eigen::Ref<Eigen::VectorXd> out, std::vector<uint32_t> idchan, std::vector<uint32_t> idfreq);
		void getfrequencies(Eigen::Ref<Eigen::MatrixXd> out, std::vector<uint32_t> freqs);

	
	public:
		pwelchconfig_t 	config;

	private:
		
	
		/*! \brief 	Pointer to the window
		 */
		Window * 	_window;

		/*! \brief 	Signal window
		 */
		Eigen::VectorXd  	_wsig;

		/*! \brief 	Complex output of fft
		 */
		Eigen::VectorXd  	_wpxx;

		/*! \brief 	FFTW3 plan
		 */
		fftw_plan 	_plan;

		Eigen::MatrixXd _psd;

		bool 		_isset;
		
	public: 
		/*! \brief Eigen flag to keep the memory block of the matrix
		 * aligned
		 */
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};
	}
}

#endif
