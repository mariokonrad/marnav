/// This example demonstrates how to do a very basic NMEA multiplexer.
/// It does not implement any error handling and other (normally necessary)
/// stuff (configurability, error handling, etc.).

#include <marnav/nmea/nmea.hpp>
#include <marnav/io/default_nmea_reader.hpp>
#include <marnav/io/serial.hpp>
#include <marnav/utils/unique.hpp>
#include <vector>

int main(int, char **)
{
	using namespace marnav;
	using namespace marnav::io;

	// prepare destinations
	std::vector<std::unique_ptr<io::serial>> destinations;
	destinations.push_back(utils::make_unique<io::serial>("dev/ttyUSB1",
		io::serial::baud::BAUD_4800, io::serial::databits::BIT_8, io::serial::stopbits::BIT_1,
		io::serial::parity::NONE));
	destinations.push_back(utils::make_unique<io::serial>("dev/ttyUSB2",
		io::serial::baud::BAUD_4800, io::serial::databits::BIT_8, io::serial::stopbits::BIT_1,
		io::serial::parity::NONE));

	// open source device
	io::default_nmea_reader source{
		utils::make_unique<serial>("/dev/ttyUSB0", serial::baud::BAUD_4800,
			serial::databits::BIT_8, serial::stopbits::BIT_1, serial::parity::NONE)};

	std::string data;
	while (source.read_sentence(data)) {
		try {
			// this is used only to check the received data, e.g. if the checksum is correct.
			auto sentence = nmea::make_sentence(data);

			// send valid NMEA sentences to destinations
			for (auto & destination : destinations) {
				destination->write(data.c_str(), data.size());
			}
		} catch (nmea::checksum_error) {
			// let's just ignore them
		}
	}
}
