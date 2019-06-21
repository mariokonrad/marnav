#ifndef MARNAV__IO__DEVICE__HPP
#define MARNAV__IO__DEVICE__HPP

#include <cstdint>

namespace marnav
{
namespace io
{
/// This is the base class for devices needed to perform IO operations.
/// It is simply an interface, no data members.
class device
{
public:
	virtual ~device() {}

	/// Opens the device.
	///
	/// @exception std::runtime_error Error on opening the device.
	virtual void open() = 0;

	/// Closes the device.
	virtual void close() = 0;

	/// Reads data from the opened device into the buffer of the specified size.
	///
	/// @param[out] buffer The buffer to contain all read data.
	/// @param[in] size The size of the buffer.
	/// @return The number of bytes read into the buffer.
	/// @exception std::invalid_argument Parameter errors (buffer is nullptr, size is zero, ...)
	/// @exception std::runtime_error Probably a read error. This does not include EOF.
	virtual int read(char * buffer, uint32_t size) = 0;

	/// Writes to the opened device.
	///
	/// @param[in] buffer Data to write.
	/// @param[in] size Number of bytes to write to the device.
	/// @return The number of bytes written to the device.
	/// @exception std::invalid_argument Parameter errors (buffer is nullptr, size is zero, ...)
	/// @exception std::runtime_error Probably a read error. This does not include EOF.
	virtual int write(const char * buffer, uint32_t size) = 0;
};
}
}

#endif
