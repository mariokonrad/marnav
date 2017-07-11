#include "default_nmea_reader.hpp"

/// @example read_nmea.cpp
/// Shows how to use the marnav::io::default_nmea_reader to read NMEA data from
/// a serial port.
///
/// The marnav::io::default_nmea_reader inherits from marnav::io::nmea_reader.

/// @example read_nmea_boostasio.cpp
/// This example also show how to read NMEA data using the marnav::io::default_nmea_reader,
/// but utilizes \c boost.asio to read from a serial port instead of marnav::io::serial.

/// @example serial_to_tcp.cpp
/// Simple demonstration of reading NMEA sentences from a serial port and forward
/// them to a TCP listener. Only valid NMEA sentences are forwarded, no other filtering
/// is taking place. This example uses \c boost.asio for both serial and TCP communication.

namespace marnav
{
namespace io
{

default_nmea_reader::default_nmea_reader(std::unique_ptr<device> && dv)
	: nmea_reader(std::move(dv))
	, received_(false)
{
}

default_nmea_reader::~default_nmea_reader()
{
}

/// Reads synchronously messages from the device.
///
/// @param[out] s The received sentence.
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error
bool default_nmea_reader::read_sentence(std::string & s)
{
	// reads as long as the sentence is not complete.
	while (read()) {

		// the sentence was received, return it and reset the 'semaphore'.
		// please note: this works only in single threaded environment,
		// since the 'semaphore' isn't really one.
		if (received_) {
			s = sentence_;
			received_ = false;
			return true;
		}
	}
	return false;
}

/// Processes the received sentence. Uses the data member 'sentence_received'
/// as poor-mans semaphore to signal the receipt.
///
/// After the reception, the message will be stored temporarily.
void default_nmea_reader::process_sentence(const std::string & s)
{
	sentence_ = s;
	received_ = true;
}
}
}
