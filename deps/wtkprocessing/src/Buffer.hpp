#ifndef PROC_BUFFER_HPP
#define PROC_BUFFER_HPP

#include <string>
#include <iostream>
#include <math.h>
#include <Eigen/Dense>

#include <wtkcore/Exception.hpp>
#include "proc_utilities.hpp"

namespace wtk {
	namespace proc {

/*! \brief Pure virtual class for buffers
 *
 * \ingroup bcitk_buffers
 *
 * This class is used to create a buffer of data. Different types of buffer are
 * (will be) available. This is a pure virtual class, it can be instanciated
 * only as derived class.
 * \sa RingBuffer
 */

class Buffer {

	public:
		/*! \brief	Constructor
		 *  \param	type	Type of buffer
		 */
		Buffer(int type);
		
		/*! \brief 	Destructor 
		 */
		~Buffer(void);
		
		virtual bool Setup(unsigned nsamples, unsigned nchannels) = 0;

		/*! \brief 	Get buffer type
		 *  \return 	The type of buffer
		 */
		virtual int GetType(void);
		
		/*! \brief 	Virtual method to add data to the buffer
		 */
		virtual void Add(const Eigen::Ref<const Eigen::MatrixXd>& in) = 0;
		
		/*! \brief 	Virtual method to return data to the buffer
		 *  \param  out Reference to the data stored in the buffer
		 */
		virtual void Get(Eigen::Ref<Eigen::MatrixXd> out);
		
		/*! \brief 	Check if buffer entries are not all set to 0
		 *  \return     True if is full, False otherwise
		 */
		virtual bool IsFull(void);

		virtual bool IsSet(void);

		/*! \brief 	Raw dump of buffer data
		 */
		virtual void Dump(void);



	public:
		/** @name 
		 * Buffer types
		 */ 
		///@{
		const static int AsRingBuffer 	= 1;
    const static int AsSimpleBuffer 	= 2;
		///@}
	
	protected:
		/*! \brief	buffer data
		 */
		Eigen::MatrixXd _buffer;
		bool _isset;
		
	private:
		/*! \brief 	buffer type
		 */
		int _type;

	public: 
		/*! \brief Eigen flag to keep the memory block of the matrix
		 * aligned
		 */
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};
	}
}

#endif
