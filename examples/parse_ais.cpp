#include <vector>
#include <iostream>
#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/vdm.hpp>
#include <marnav/ais/ais.hpp>
#include <marnav/ais/message_05.hpp>

int main(int, char **)
{
	using namespace marnav;

	// received NMEA sentences
	const std::vector<std::string> received_strings
		= {"!AIVDM,2,1,3,B,55P5TL01VIaAL@7WKO@mBplU@<PDhh000000001S;AJ::4A80?4i@E53,0*3E",
			"!AIVDM,2,2,3,B,1@0000000000000,2*55"};

	// parse NMEA sentences
	std::vector<std::unique_ptr<nmea::sentence>> sentences;
	for (auto const & txt : received_strings) {
		auto sentence = nmea::make_sentence(txt);
		if (sentence->id() == nmea::sentence_id::VDM) {
			sentences.push_back(std::move(sentence));
		}
	}

	// parse and and process AIS messags
	auto payload = nmea::collect_payload(sentences.begin(), sentences.end());
	auto message = ais::make_message(payload);
	if (message->type() == ais::message_id::static_and_voyage_related_data) {
		auto report = ais::message_cast<ais::message_05>(message);
		std::cout << "shipname: " << report->get_shipname() << "\n";
		std::cout << "callsign: " << report->get_callsign() << "\n";
	}

	return 0;
}
