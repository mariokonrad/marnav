#include <marnav/ais/message_01.hpp>
#include <marnav/ais/ais.hpp>
#include <marnav/nmea/vdm.hpp>
#include <iostream>

int main(int, char **)
{
	using namespace marnav;

	// prepare AIS data
	ais::message_01 pos_report;
	pos_report.set_sog(marnav::units::knots{8.2});
	// ... most data not shown here

	// create payload
	auto payload = ais::encode_message(pos_report);

	// create NMEA sentences
	for (uint32_t fragment = 0; fragment < payload.size(); ++fragment) {
		nmea::vdm vdm;
		vdm.set_n_fragments(payload.size());
		vdm.set_fragment(fragment + 1);
		vdm.set_radio_channel(nmea::ais_channel::B);
		vdm.set_payload(payload[fragment]);

		// collect, send or do something with the sentence...
		std::string s = nmea::to_string(vdm);
		std::cout << s << "\n";
	}
}
