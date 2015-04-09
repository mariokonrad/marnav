#include <marnav/io/default_nmea_reader.hpp>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/io.hpp>
#include <iostream>

int main(int, char **)
{
	using namespace marnav;

	// create and open the device for reading.
	io::default_nmea_reader reader{"/dev/ttyUSB0"};

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
