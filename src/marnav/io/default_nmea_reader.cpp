#include "default_nmea_reader.hpp"

namespace marnav
{
namespace io
{

default_nmea_reader::default_nmea_reader(const std::string & port)
	: nmea_serial(port)
	, received(false)
{
}

default_nmea_reader::default_nmea_reader(std::unique_ptr<device> && dev)
	: nmea_serial(std::move(dev))
	, received(false)
{
}

default_nmea_reader::~default_nmea_reader() {}

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
		if (received) {
			s = sentence;
			received = false;
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
	sentence = s;
	received = true;
}
}
}
