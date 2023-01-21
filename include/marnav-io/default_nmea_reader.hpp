#ifndef MARNAV_IO_DEFAULT_NMEA_READER_HPP
#define MARNAV_IO_DEFAULT_NMEA_READER_HPP

#include <marnav-io/nmea_reader.hpp>

namespace marnav::io
{
/// This is a very simple NMEA sentence reader, meant for synchronous
/// and single threaded reading from a serial port or a device.
///
/// @example nmea_multiplexer.cpp
class default_nmea_reader : public nmea_reader
{
public:
	~default_nmea_reader() override = default;

	default_nmea_reader() = delete;
	default_nmea_reader(std::unique_ptr<device> &&);
	default_nmea_reader(const default_nmea_reader &) = delete;
	default_nmea_reader(default_nmea_reader &&) = default;

	default_nmea_reader & operator=(const default_nmea_reader &) = delete;
	default_nmea_reader & operator=(default_nmea_reader &&) = default;

	bool read_sentence(std::string & s);

protected:
	void process_sentence(const std::string & s) override;

private:
	bool received_;
	std::string sentence_;
};
}

#endif
