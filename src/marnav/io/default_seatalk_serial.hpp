#ifndef MARNAV__IO__DEFAULT_SEATALK_SERIAL__HPP
#define MARNAV__IO__DEFAULT_SEATALK_SERIAL__HPP

#include <marnav/io/serial.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace io
{
/// Returns a serial device with the default configuration for reading SeaTalk.
///
/// @note The default parameters are not valid in every case, depending on the device.
///
/// @param [in] port The device name.
/// @return The serial device object, default configured.
inline std::unique_ptr<serial> make_default_seatalk_serial(const std::string & port)
{
	return utils::make_unique<serial>(port, serial::baud::baud_4800, serial::databits::bit_8,
		serial::stopbits::bit_1, serial::parity::mark);
}
}
}

#endif
