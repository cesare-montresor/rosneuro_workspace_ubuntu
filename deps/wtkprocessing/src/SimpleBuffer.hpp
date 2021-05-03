#ifndef PROC_SIMPLEBUFFER_HPP
#define PROC_SIMPLEBUFFER_HPP

#include <string>
#include <math.h>
#include <Eigen/Dense>

#include "Buffer.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a simple  buffer
 *
 * \ingroup bcitk_buffers
 *
 * This class derives from Buffer. It implements a ring circular buffer.
 * \sa Buffer
 */

class SimpleBuffer : public Buffer {

	public:
		/*! \brief	TO CHANGE Constructor. The buffer is
		 * 		initialized wint NaN values
		 *  \param	nsamples	Number of samples in the buffer
		 *  \param	nchannels	Number of channels in the buffer
		 *  (default: 1)
		 */
		SimpleBuffer(void);
		
		/*! \brief 	Destructor 
		 */
		~SimpleBuffer(void);

		bool Setup(unsigned int nsamples, unsigned int nchannels);
		
		/*! \brief 		Add data frame to the buffer
		 *  \param 	in	Frame of data in the format of [samples x channels]
		 *  \par 		Example:
		 *  \include		Buffer/ringbuffer.cpp
		 */
		void Add(const Eigen::Ref<const Eigen::MatrixXd>& in);

    void Reset(void);



};
  } //namespace proc
} // namespace wtk

#endif
