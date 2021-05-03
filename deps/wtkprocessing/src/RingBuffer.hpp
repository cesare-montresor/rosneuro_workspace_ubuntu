#ifndef PROC_RINGBUFFER_HPP
#define PROC_RINGBUFFER_HPP

#include <string>
#include <math.h>
#include <Eigen/Dense>

#include "Buffer.hpp"

namespace wtk {
	namespace proc {

/*! \brief This class implements a ring circular buffer
 *
 * \ingroup bcitk_buffers
 *
 * This class derives from Buffer. It implements a ring circular buffer.
 * \sa Buffer
 */

class RingBuffer : public Buffer {

	public:
		/*! \brief	TO CHANGE Constructor. The buffer is
		 * 		initialized wint NaN values
		 *  \param	nsamples	Number of samples in the buffer
		 *  \param	nchannels	Number of channels in the buffer
		 *  (default: 1)
		 */
		RingBuffer(void);
		
		/*! \brief 	Destructor 
		 */
		~RingBuffer(void);

		bool Setup(unsigned int nsamples, unsigned int nchannels);
		
		/*! \brief 		Add data frame to the buffer
		 *  \param 	in	Frame of data in the format of [samples x channels]
		 *  \par 		Example:
		 *  \include		Buffer/ringbuffer.cpp
		 */
		void Add(const Eigen::Ref<const Eigen::MatrixXd>& in);

};
	}
}

#endif
