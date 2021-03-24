#include <marnav/io/default_nmea_reader.hpp>
#include <marnav/io/default_nmea_serial.hpp>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>
#include <iostream>

int main(int, char **)
{
	using namespace marnav;
	using namespace marnav::io;

	// create and open the device for reading.
	default_nmea_reader reader{make_default_nmea_serial("/dev/ttyUSB0")};

	std::string data;

	// read and process NMEA sentences, bus synchronization is done automatically.
	while (reader.read_sentence(data)) {
		// data was successfully read from the NMEA bus, inclusive synchronization
		// of NMEA sentences. This means it is possible to begin to listen on the
		// bus at any time.
		auto sentence = nmea::make_sentence(data);

		// do something with the sentence, for example dump the position
		if (sentence->id() == nmea::sentence_id::RMC) {
			auto rmc = nmea::sentence_cast<nmea::rmc>(sentence.get());
			std::cout << "latitude : " << nmea::to_string(rmc->get_lat()) << "\n";
			std::cout << "longitude: " << nmea::to_string(rmc->get_lon()) << "\n";
		}
	}
}
