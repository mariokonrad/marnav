#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/nrx.hpp>
#include <iostream>
#include <vector>

int main(int, char **)
{
	using namespace marnav;

	// received NMEA sentences
	//	const std::vector<std::string> received_strings = {
	//		"$CRNRX,007,001,00,IE69,1,135600,27,06,2001,241,3,A,==========================*09",
	//		"$CRNRX,007,002,00,,,,,,,,,,========^0D^0AISSUED ON SATURDAY 06 JANUARY 2001.*29",
	//		"$CRNRX,007,003,00,,,,,,,,,,^0D^0AINSHORE WATERS FORECAST TO 12 MILES^0D^0AOFF*0D",
	//		"$CRNRX,007,004,00,,,,,,,,,,SHORE FROM 1700 UTC TO 0500 UTC.^0D^0A^0D^0ANORT*1E",
	//		"$CRNRX,007,005,00,,,,,,,,,,H FORELAND TO SELSEY BILL.^0D^0A12 HOURS FOREC*09",
	//		"$CRNRX,007,006,00,,,,,,,,,,AST:^0D^0A^0ASHOWERY WINDS^2C "
	//		"STRONGEST IN NORTH.^0D*16",
	//		"$CRNRX,007,007,00,,,,,,,,,,^0A^0A*79",
	//	};

	const std::vector<std::string> received_strings
		= {"$CRNRX,011,001,15,IB45,2,,,,,426,0,A,IB45 ^0D^0A260909 UTC MAR 07^0D^0AWWJP83 *21",
			"$CRNRX,011,002,15,,,,,,,,,,RJTD 260600^0D^0AVITAL WARNING FOR YOKOHAMA NAVTEX*00",
			"$CRNRX,011,003,15,,,,,,,,,, AREA ^0D^0A260600UTC ISSUED AT 260900UTC^0D^0ACOLD*4A",
			"$CRNRX,011,004,15,,,,,,,,,, FRONT FROM 48N 157E T O 42N 156E 36N^0D^0A 151E 30*23",
			"$CRNRX,011,005,15,,,,,,,,,,N 147E 25N 140E^0D^0AGALE WARNING WESTERN SEA OFF *6C",
			"$CRNRX,011,006,15,,,,,,,,,,SANRIKU ^0D^0AWITH MAX WINDS 35 KNOTS^0D^0AWARNING*12",
			"$CRNRX,011,007,15,,,,,,,,,,(NEAR GALE) EASTERN SEA OFF^0D^0ASANRIKU^2C NORTH*32",
			"$CRNRX,011,008,15,,,,,,,,,,ERN SEA OFF KANTO^2C^0D^0ASOUTHERN SEA OFF KANTO*0A",
			"$CRNRX,011,009,15,,,,,,,,,,^2C EASTERN SEA OFF ^0D^0ATOKAI^0D^0ANEXT WARNING *0C",
			"$CRNRX,011,010,15,,,,,,,,,,WILL BE ISSUED BEFORE ^0D^0A261500UTC^0D^0A=^0D^0A*1B",
			"$CRNRX,011,011,15,,,,,,,,,,^0D^0ANNNN^0D^0A *5D"};

	// parse NMEA sentences
	std::vector<std::unique_ptr<nmea::sentence>> sentences;
	for (auto const & txt : received_strings) {
		auto sentence = nmea::make_sentence(txt);
		if (sentence->id() == nmea::sentence_id::NRX) {
			sentences.push_back(std::move(sentence));
		}
	}

	// parse and process NRX messags
	uint32_t last_sequence = 0;
	std::for_each(std::begin(sentences), std::end(sentences),
		[&](std::unique_ptr<nmea::sentence> & sentence) {
			auto nrx = nmea::sentence_cast<nmea::nrx>(sentence);

			if (last_sequence + 1 != nrx->get_sentence_number()) {
				std::cout << "invalid sequence" << std::endl;
				return;
			}

			last_sequence = nrx->get_sentence_number();
			if (nrx->get_message().has_value()) {
				std::cout << nrx->get_parsed_message().value_or("");
			}
		});

	return 0;
}
