#ifndef __IO__NMEA_READER__HPP__
#define __IO__NMEA_READER__HPP__

#include <marnav/io/device.hpp>
#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace io
{
/// This class reads NMEA sentences from a device. Normally this would
/// be a serial character device (e.g. \c /dev/ttyS0 or \c /dev/ttyUSB0).
///
/// In order to use this NMEA reader, it must be subclassed.
///
class nmea_reader
{
public:
	virtual ~nmea_reader();

	nmea_reader(std::unique_ptr<device> && dev);
	nmea_reader(const nmea_reader &) = delete;
	nmea_reader(nmea_reader &&) = default;

	nmea_reader & operator=(const nmea_reader &) = delete;
	nmea_reader & operator=(nmea_reader &&) = default;

	void close();
	bool read();

protected:
	virtual void process_sentence(const std::string &) = 0;

private:
	void process_nmea();
	bool read_data();

	char raw;
	std::string sentence;
	std::unique_ptr<device> dev; ///< Device to read data from.
};
}
}

#endif
