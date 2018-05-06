#ifndef MARNAV__IO__DEFAULT_NMEA_READER__HPP
#define MARNAV__IO__DEFAULT_NMEA_READER__HPP

#include <marnav/io/nmea_reader.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace io
{
/// This is a very simple NMEA sentence reader, meant for synchronous
/// and single threaded reading from a serial port or a device.
///
/// @example nmea_multiplexer.cpp
class MARNAV_EXPORT default_nmea_reader : public nmea_reader
{
public:
	virtual ~default_nmea_reader();

	default_nmea_reader() = delete;
	default_nmea_reader(std::unique_ptr<device> &&);
	default_nmea_reader(const default_nmea_reader &) = delete;
	default_nmea_reader(default_nmea_reader &&) = default;

	default_nmea_reader & operator=(const default_nmea_reader &) = delete;
	default_nmea_reader & operator=(default_nmea_reader &&) = default;

	bool read_sentence(std::string & s);

protected:
	virtual void process_sentence(const std::string & s) override;

private:
	bool received_;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
	std::string sentence_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};
}
}

#endif
