#ifndef __IO__NMEA_READER__HPP__
#define __IO__NMEA_READER__HPP__

#include <marnav/io/device.hpp>
#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace io
{

/// This class reads NMEA sentences from a device. Normally this would
/// be a serial character device (e.g. /dev/ttyS0 or /dev/ttyUSB0).
///
/// In order to use this NMEA reader, it must be subclassed.
///
/// @example read_nmea.cpp
class nmea_reader
{
public:
	nmea_reader(std::unique_ptr<device> && dev);
	virtual ~nmea_reader();

	void close();
	bool read() throw(std::runtime_error, std::length_error);

protected:
	virtual void process_sentence(const std::string &) = 0;

private:
	void process_nmea() throw(std::length_error);
	bool read_data() throw(std::runtime_error);

	char raw;
	std::string sentence;
	std::unique_ptr<device> dev; ///< Device to read data from.
};
}
}

#endif
