/// This example shows how to use Boost.ASIO in order to read synchronously
/// NMEA data from a serial port.

#include <iostream>
#include <boost/asio.hpp>
#include <marnav/io/default_nmea_reader.hpp>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav_example
{

/// Synchronous reading of the serial port using Boost.ASIO
class boost_asio_serial : public marnav::io::device
{
public:
	boost_asio_serial(const std::string & port)
		: io()
		, serial(io, port)
	{
		serial.set_option(boost::asio::serial_port_base::baud_rate(4800));
	}

	virtual void open() override {}

	virtual void close() override { serial.close(); }

	virtual int read(char * buffer, uint32_t size) override
	{
		if ((buffer == nullptr) || (size == 0))
			throw std::invalid_argument{"invalid buffer or size"};
		if (!serial.is_open())
			throw std::runtime_error{"device not open"};

		return boost::asio::read(serial, boost::asio::buffer(buffer, size));
	}

	virtual int write(const char *, uint32_t) override
	{
		throw std::runtime_error{"operation not supported"};
	}

private:
	boost::asio::io_service io;
	boost::asio::serial_port serial;
};

/// This subclassing is not really necessary, but hides the instantiation
/// of boost_asio_serial from normal usage (see function 'main'). This way
/// it is completley transparent whether or not Boost.ASIO is in use or not
/// from the perspective of just using it.
class sentence_reader : public marnav::io::default_nmea_reader
{
public:
	sentence_reader(const std::string & port)
		: default_nmea_reader(std::unique_ptr<marnav::io::device>{new boost_asio_serial{port}})
	{
	}
};
}

int main(int, char **)
{
	using namespace marnav;

	// create and open the device for reading.
	marnav_example::sentence_reader reader{"/dev/ttyUSB0"};

	std::string data;

	// read and process NMEA sentences, bus synchronization is done automatically.
	while (reader.read_sentence(data)) {
		// data was successfully read from the NMEA bus, inclusive synchronization
		// of NMEA sentences. This means it is possible to begin to listen on the
		// bus at any time.
		auto sentence = nmea::make_sentence(data);

		// do something with the sentence, for example dump the position
		if (sentence->id() == nmea::sentence_id::RMC) {
			auto rmc = nmea::sentence_cast<nmea::rmc>(sentence);
			std::cout << "latitude : " << nmea::to_string(rmc->get_latitude()) << "\n";
			std::cout << "longitude: " << nmea::to_string(rmc->get_longitude()) << "\n";
		}
	}
}
