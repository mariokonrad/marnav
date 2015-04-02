#ifndef __IO__DEVICE__HPP__
#define __IO__DEVICE__HPP__

#include <stdint.h>
#include <stdexcept>

namespace io
{

/// This is the base class for devices needed to perform IO operations.
/// It is simply an interface, no data members.
class device
{
public:
	/// Opens the device.
	virtual void open() throw(std::runtime_error) = 0;

	/// Closes the device.
	virtual void close() = 0;

	/// Reads data from the opened device into the buffer of the specified size.
	///
	/// @retval The number of bytes read into the buffer.
	virtual int read(char* buffer, uint32_t size) throw(std::invalid_argument, std::runtime_error)
		= 0;
};
}

#endif
