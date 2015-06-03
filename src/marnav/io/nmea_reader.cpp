#include "nmea_reader.hpp"
#include <marnav/utils/unique.hpp>
#include <algorithm>

namespace marnav
{
namespace io
{
nmea_reader::nmea_reader(std::unique_ptr<device> && dev)
	: raw(0)
	, dev(std::move(dev))
{
}

void nmea_reader::close()
{
	if (dev)
		dev->close();
	dev.reset();
}

/// Reads data from the device.
///
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error The device was invalid or read error.
bool nmea_reader::read_data() throw(std::runtime_error)
{
	if (!dev)
		throw std::runtime_error{"device invalid"};
	int rc = dev->read(reinterpret_cast<char *>(&raw), sizeof(raw));
	if (rc == 0)
		return false;
	if (rc < 0)
		throw std::runtime_error{"read error"};
	if (rc != sizeof(raw))
		throw std::runtime_error{"read error"};
	return true;
}

/// Processes the data read from the device.
///
/// @exception std::runtime_error
void nmea_reader::process_nmea() throw(std::runtime_error)
{
	switch (raw) {
		case '\r':
			break;
		case '\n': // end of sentence
			process_sentence(sentence);
			sentence.clear();
			break;
		default:
			if (sentence.size() >= nmea::sentence::MAX_LENGTH)
				throw std::runtime_error{"sentence size to large. receiving NMEA data?"};
			sentence += raw;
			break;
	}
}

/// Reads data from the device and processes it. If a complete NMEA
/// sentence was received the method process_message will be executed.
/// This method automatcially synchronizes with NMEA data.
///
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error Device or processing error.
bool nmea_reader::read() throw(std::runtime_error)
{
	if (!read_data())
		return false;
	process_nmea();
	return true;
}
}
}
