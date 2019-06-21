#ifndef MARNAV__IO__NMEA_READER__HPP
#define MARNAV__IO__NMEA_READER__HPP

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
/// This reader opens the device upon construction.
///
class nmea_reader
{
public:
	virtual ~nmea_reader();

	nmea_reader(std::unique_ptr<device> && d);
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

	char raw_;
	std::string sentence_;
	std::unique_ptr<device> dev_; ///< Device to read data from.
};
}
}

#endif
