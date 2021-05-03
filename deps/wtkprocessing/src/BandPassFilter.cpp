#ifndef PROC_BANDPASSFILTER_CPP
#define PROC_BANDPASSFILTER_CPP



namespace wtk {
  namespace proc {

/*! \brief This class implements a band pass filter in frequency domain
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter. It implements a band filter in frequency domain
 * according to the equation:
 *
 *
 *
 *
 *
 *
 *
 * The input and output data are in the format [samples x channels].
 * \sa Filter
 */

class BandPassFilter : public Filter {

  public:
    /*! \brief	Constructor.
     */
    BandPassFilter(void);

    /*! \brief	Destructor.
     */
    ~BandPassFilter(void);

    /*! \brief 	Implementation of the main method. It applies
     * 		the dc filter.
     *  \param in 	Input data matrix
     *  \param out	Output data matrix
     */
     virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& in, Eigen::Ref<Eigen::MatrixXd> out);

   private:

    float lower_cut_off;
    float upper_cut_off;
};

  }
}
