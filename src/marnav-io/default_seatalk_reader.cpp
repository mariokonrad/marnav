#include <marnav-io/default_seatalk_reader.hpp>

/// @example simple_seatalk_nmea_converter.cpp
/// This is a very simplistic conversion from SeaTalk messages to NMEA sentences.
///
/// SeaTalk message are being read from a serial port, converted to a corresponding
/// NMEA message, which is sent on another serial port.
///
/// This example uses the marnav::io::default_seatalk_reader to read SeaTalk
/// messages and \c boost.asio to send NMEA sentences.

namespace marnav
{
namespace io
{
default_seatalk_reader::default_seatalk_reader(std::unique_ptr<device> && dv)
	: seatalk_reader(std::move(dv))
	, message_received_(false)
{
}

/// Reads synchronously messages from the device.
///
/// @param[out] data The received message.
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error
bool default_seatalk_reader::read_message(seatalk::raw & data)
{
	// reads as long as the message is not complete.
	while (read()) {
		// the message was received, return it and reset the 'semaphore'.
		// please note: this works only in single threaded environment,
		// since the 'semaphore' isn't really one.
		if (message_received_) {
			data = message_;
			message_received_ = false;
			return true;
		}
	}
	return false;
}

/// Processes the received message. Uses the data member 'message_received'
/// as poor-mans semaphore to signal the receipt.
///
/// After the reception, the message will be stored temporarily.
void default_seatalk_reader::process_message(const seatalk::raw & msg)
{
	message_ = msg;
	message_received_ = true;
}
}
}
