/// This example shows how to use Boost.ASIO in order to read synchronously
/// NMEA data from a serial port.

#include <boost/asio.hpp>
#include <marnav/io/nmea_serial.hpp>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/io.hpp>
#include <iostream>

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

	virtual void open() throw(std::runtime_error) override {}

	virtual void close() override { serial.close(); }

	virtual int read(char * buffer, uint32_t size) throw(
		std::invalid_argument, std::runtime_error) override
	{
		if ((buffer == nullptr) || (size == 0))
			throw std::invalid_argument{"invalid buffer or size"};
		if (!serial.is_open())
			throw std::runtime_error{"device not open"};

		return boost::asio::read(serial, boost::asio::buffer(buffer, size));
	}

private:
	boost::asio::io_service io;
	boost::asio::serial_port serial;
};

/// @note This is the exact same implemenation like in the example read_nmea.cpp
class sentence_reader : public marnav::io::nmea_serial
{
public:
	sentence_reader(const std::string & port)
		: nmea_serial(std::unique_ptr<marnav::io::device>{new boost_asio_serial{port}})
		, sentence_received(false)
	{
	}

	/// Reads synchronously messages from the device.
	///
	/// @param[out] s The received sentence.
	/// @retval true  Success.
	/// @retval false End of file.
	/// @exception std::runtime_error
	bool read_sentence(std::string & s)
	{
		// reads as long as the sentence is not complete.
		while (read()) {

			// the sentence was received, return it and reset the 'semaphore'.
			// please note: this works only in single threaded environment,
			// since the 'semaphore' isn't really one.
			if (sentence_received) {
				s = sentence;
				sentence_received = false;
				return true;
			}
		}
		return false;
	}

protected:
	/// Processes the received sentence. Uses the data member 'sentence_received'
	/// as poor-mans semaphore to signal the receipt.
	///
	/// After the reception, the message will be stored temporarily.
	virtual void process_sentence(const std::string & s) override
	{
		sentence = s;
		sentence_received = true;
	}

private:
	bool sentence_received;
	std::string sentence;
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
			std::cout << "latitude : " << nmea::to_string(rmc->get_lat()) << "\n";
			std::cout << "longitude: " << nmea::to_string(rmc->get_lon()) << "\n";
		}
	}
}
