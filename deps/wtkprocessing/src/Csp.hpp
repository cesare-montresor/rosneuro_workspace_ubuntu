#ifndef PROC_CSP_HPP
#define PROC_CSP_HPP

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

// Edited by L.Tonin  <luca.tonin@epfl.ch> on 22/07/19 10:21:21
// For std::iota function
#include <numeric>		

#include <wtkcore/Exception.hpp>

#include "Filter.hpp"
#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a Common Spatial Pattern filter in spatial domain
 *
 * \ingroup bcitk_filters
 *
 * This class derives from Filter. It implements a Common Spatial Pattern filter in spatial domain
 * according to the equation:
 * 
 * \f[
 *	 out(t) = in(t) * csp_coefficients'
 * \f]
 *
 * where \f$out(t)\f$ is the resulting filtered data at time \f$t\f$,
 * \f$in(t)\f$ is the input data at time \f$t\f$ and \f$csp_coefficients\f$
 * are the CSP filters coefficents. Input and output data are in the format S
 * samples x N channels, while the CSP coefficients matrix is a rectangular matrix
 * K x N where K is the number of desired patterns.
 * \sa Filter
 */

typedef struct {
	std::string  filename;
  std::string  subject;
  unsigned int num_channels;
  unsigned int num_patterns;
  unsigned int num_filters;
} cspconfig_t;

class Csp : public Filter {
	
	public:
    Csp(void);

    Csp(std::string filename, const int csp_num  = 0);

		/*! \brief	Destructor.
		 */
    ~Csp(void);

    /*! \brief	Setup.
     *  \param ext_csp_coefficients and ext_csp_map Path to external binary files with the respective
     *        data structure
     */
    bool Setup(std::string filename, const int csp_num  = 0);

		/*! \brief	Setup.
     *  \param data_in Pointer to memory where the data are stored.
     *		    (pointer to double matrix MxN where M are the number of samples and N the number of signals
     *  \param data_labels Pointer to memory where the labels are sored.
     *        (pointer to int vector Mx1, where M is the same value of data_in
     */
    bool Setup(const Eigen::Ref<const Eigen::MatrixXd>& data_in, const std::vector<uint32_t>& data_labels,
               const int csp_num = 0, std::string subject = "");

    /*! \brief 	Get CSP filter coefficients
		 *  \param mask	The current mask
		 */
    void GetCspCoefficients(Eigen::Ref<Eigen::MatrixXd> csp_coefficients);

    /*! \brief 	Store new CSP coefficient
     *  \param csp_coefficients Pointer to memory where the filter coefficients are stored.
     *		    (e.g., pointer to array)
     */
    void SetCspCoefficients(const Eigen::Ref<const Eigen::MatrixXd>& csp_coefficients);

    /*! \brief 	Get CSP map of the corresponding indexes between outward spatial patterns
     * and input signals
     *  \param csp_map map of the corresponding indexes between outward spatial patterns and input signals
     */
    void GetCspMap(std::vector<uint32_t>& csp_map);

    /*! \brief 	Store new CSP map of the corresponding indexes between outward spatial patterns
     *  and input signals
     *  \param csp_map map of the corresponding indexes between outward spatial patterns and input signals
     */
    void SetCspMap(const std::vector<uint32_t>& csp_map);

    /*! \brief 	Store new CSP number of patterns
     *  \param csp_num Number of patterns to be computed
     */
    void SetCspNumPatterns(const int csp_num);

    /*! \brief 	Get CSP W matrix transformation input signals to sinergies
     *  \param W transformation matrix
     */
    void GetW(Eigen::Ref<Eigen::MatrixXd> W);

    /*! \brief 	Implementation of the main method. It applies
     * 		the CSP filter.
     *  \param in 	Input data matrix
     *  \param out	Output data matrix
     */
    virtual void Apply(const Eigen::Ref<const Eigen::MatrixXd>& data_in, Eigen::Ref<Eigen::MatrixXd> data_out);

		virtual bool IsSet(void);
	
		void Dump(void);
	
	public:
    cspconfig_t	config_;
	protected:
    bool isset_;

	private:
		/*! \brief 	The mask stored
		 */
    Eigen::MatrixXd csp_coefficients_;
    std::vector<uint32_t> csp_map_;

    std::string _stype;


};
	}
}

#endif
