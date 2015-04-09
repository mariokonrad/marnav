#ifndef __IO__DEFAULT_NMEA_READER__HPP__
#define __IO__DEFAULT_NMEA_READER__HPP__

#include <marnav/io/nmea_serial.hpp>

namespace marnav
{
namespace io
{

/// This is a very simple NMEA sentence reader, meant for synchronous
/// and single threaded reading from a serial port or a device.
class default_nmea_reader : public nmea_serial
{
public:
	default_nmea_reader(const std::string & port);
	default_nmea_reader(std::unique_ptr<device> && dev);
	virtual ~default_nmea_reader();
	bool read_sentence(std::string & s);

protected:
	virtual void process_sentence(const std::string & s) override;

private:
	bool received;
	std::string sentence;
};
}
}

#endif
