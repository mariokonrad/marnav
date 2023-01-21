// This example shows how to receive NMEA sentences on a port, check them
// and forward it to a TCP server, which listens for sentences.
//
// Boost.ASIO is used for both, serial and TCP connections.

#include <marnav/nmea/nmea.hpp>
#include <marnav-io/default_nmea_reader.hpp>
#include <boost/asio.hpp>

namespace marnav_example
{
/// Synchronous reading of the serial port using Boost.ASIO
///
/// @note Inline implemented for easier reading within this example.
class boost_asio_serial : public marnav::io::device
{
public:
	boost_asio_serial(const std::string & port, int baud_rate = 4800)
		: io_()
		, serial_(io_, port)
	{
		serial_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
	}

	void open() override{};

	void close() override { serial_.close(); }

	int read(char * buffer, uint32_t size) override
	{
		if ((buffer == nullptr) || (size == 0))
			throw std::invalid_argument{"invalid buffer or size"};
		if (!serial_.is_open())
			throw std::runtime_error{"device not open"};
		return boost::asio::read(serial_, boost::asio::buffer(buffer, size));
	}

	int write(const char * buffer, uint32_t size) override
	{
		if (buffer == nullptr)
			throw std::invalid_argument{"invalid buffer"};
		if (!serial_.is_open())
			throw std::runtime_error{"device not open"};
		return boost::asio::write(serial_, boost::asio::buffer(buffer, size));
	}

private:
	boost::asio::io_service io_;
	boost::asio::serial_port serial_;
};

/// Blocking TCP client
///
/// @note Inline implemented for easier reading within this example.
class boost_asio_tcp_client
{
public:
	boost_asio_tcp_client(const std::string & host, const std::string & port)
		: io_()
		, socket_(io_)
	{
		boost::asio::ip::tcp::resolver resolver{io_};
		boost::asio::connect(socket_, resolver.resolve({host, port}));
	}

	~boost_asio_tcp_client() = default;

	int write(const char * buffer, uint32_t size)
	{
		if (buffer == nullptr)
			throw std::invalid_argument{"invalid buffer or size"};
		if (!socket_.is_open())
			throw std::runtime_error{"device not open"};
		return boost::asio::write(socket_, boost::asio::buffer(buffer, size));
	}

private:
	boost::asio::io_service io_;
	boost::asio::ip::tcp::socket socket_;
};
}

int main(int, char **)
{
	using namespace marnav;
	using namespace marnav_example;

	// open input port and reader
	io::default_nmea_reader input{std::make_unique<boost_asio_serial>("/dev/ttyUSB0", 38400)};

	// open output port (TCP client), default port of certain navigational software
	boost_asio_tcp_client output{"127.0.0.1", "2947"};

	std::string data;

	// read and process NMEA sentences, bus synchronization is done automatically.
	while (input.read_sentence(data)) {
		try {
			// data was successfully read from the NMEA bus, inclusive synchronization
			// of NMEA sentences. This means it is possible to begin to listen on the
			// bus at any time.
			auto sentence = nmea::make_sentence(data);

			// valid sentence was received, forward it
			output.write(data.c_str(), data.size());
		} catch (std::exception & e) {
			// ignore unknown sentences and other stuff
		}
	}

	return 0;
}
