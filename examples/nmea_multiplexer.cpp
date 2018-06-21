/// This example demonstrates how to do a very basic NMEA multiplexer.
/// It does not implement any error handling and other (normally necessary)
/// stuff (configurability, error handling, etc.).

#include <vector>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/checksum.hpp>
#include <marnav/io/default_nmea_reader.hpp>
#include <marnav/io/serial.hpp>
#include <marnav/utils/unique.hpp>

int main(int, char **)
{
	using namespace marnav;
	using namespace marnav::io;

	// prepare destinations
	std::vector<std::unique_ptr<serial>> destinations;
	destinations.push_back(utils::make_unique<serial>("dev/ttyUSB1", serial::baud::baud_4800,
		serial::databits::bit_8, serial::stopbits::bit_1, serial::parity::none));
	destinations.push_back(utils::make_unique<serial>("dev/ttyUSB2", serial::baud::baud_4800,
		serial::databits::bit_8, serial::stopbits::bit_1, serial::parity::none));

	// open source device
	default_nmea_reader source{
		utils::make_unique<serial>("/dev/ttyUSB0", serial::baud::baud_4800,
			serial::databits::bit_8, serial::stopbits::bit_1, serial::parity::none)};

	std::string data;
	while (source.read_sentence(data)) {
		try {
			// this is used only to check the received data, e.g. if the checksum is correct.
			auto sentence = nmea::make_sentence(data);

			// send valid NMEA sentences to destinations
			for (auto & destination : destinations) {
				destination->write(data.c_str(), data.size());
			}
		} catch (nmea::checksum_error &) {
			// let's just ignore them
		}
	}
}
