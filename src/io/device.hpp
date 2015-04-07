#ifndef __IO__DEVICE__HPP__
#define __IO__DEVICE__HPP__

#include <cstdint>
#include <stdexcept>

namespace marnav
{
namespace io
{

/// This is the base class for devices needed to perform IO operations.
/// It is simply an interface, no data members.
class device
{
public:
	/// Opens the device.
	///
	/// @exception std::runtime_error Error on opening the device.
	virtual void open() throw(std::runtime_error) = 0;

	/// Closes the device.
	virtual void close() = 0;

	/// Reads data from the opened device into the buffer of the specified size.
	///
	/// @param[out] buffer The buffer to contain all read data.
	/// @param[in] size The size of the buffer.
	/// @retval The number of bytes read into the buffer.
	/// @exception std::invalid_argument Parameter errors (buffer is nullptr, size is zero, ...)
	/// @exception std::runtime_error Probably a read error. This does not include EOF.
	virtual int read(char * buffer, uint32_t size) throw(
		std::invalid_argument, std::runtime_error) = 0;
};
}
}

#endif
