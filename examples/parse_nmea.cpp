#include <iostream>
#include <nmea/nmea.hpp>
#include <nmea/rmc.hpp>
#include <nmea/angle.hpp>
#include <nmea/io.hpp>

int main(int, char**)
{
	using namespace nmea;

	std::string original = "$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17";
	auto s = make_sentence(original);
	auto rmc = sentence_cast<nmea::rmc>(s);
	std::cout << "original : " << original << "\n";
	std::cout << "tag      :    " << rmc->tag() << "\n";
	std::cout << "time     :        " << to_string(rmc->get_time_utc()) << "\n";
	std::cout << "status   :               " << to_string(rmc->get_status()) << "\n";
	std::cout << "latitude :                 " << to_string(rmc->get_lat()) << "\n";
	std::cout << "lat hem  :                           " << to_string(rmc->get_lat_hem()) << "\n";
	std::cout << "longitude:                             " << to_string(rmc->get_lon()) << "\n";
	std::cout << "lon hem  :                                        " << to_string(rmc->get_lon_hem()) << "\n";
}
