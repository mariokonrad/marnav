#include <iostream>
#include <marnav/ais/message_01.hpp>
#include <marnav/ais/ais.hpp>
#include <marnav/nmea/ais_helper.hpp>

int main(int, char **)
{
	using namespace marnav;

	// prepare AIS data
	ais::message_01 pos_report;
	pos_report.set_sog(82);
	// ... most data not shown here

	// create payload
	auto payload = ais::encode_message(pos_report);

	// create NMEA sentences
	auto sentences = nmea::make_vdms(payload);

	// process sentences, somehow...
	for (auto const & sentence : sentences) {
		std::cout << nmea::to_string(*sentence) << "\n";
	}
}
