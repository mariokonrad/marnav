marnav
======

[![Build Status](https://travis-ci.org/mariokonrad/marnav.svg?branch=master)](https://travis-ci.org/mariokonrad/marnav)


Copyright (c) 2015, Mario Konrad "mario.konrad@gmx.net"

This is a C++11 library for MARitime NAVigation purposes.

It supports (partially):
- NMEA-0183 (sentences: AAM, ALM, APB, BOD, BWC, BWR, BWW, DBT, DPT, DSC, DSE, DTM, FSI, GBS,
  GGA, GLC, GLL, GNS, GRS, GSA, GST, GSV, GTD, HDG, HFB, HSC, ITS, LCD, MSK, MSS, MTW, MWD, MWV,
  OSD, RMA, RMB, RMC, ROT, RPM, RSA, RSD, RTE, SFI, TDS, TFI, TLL, TPC, TPR, TPT, TTM, VBW, VDM,
  VDO, VDR, VHW, VLW, VTG, VWR, VPW, WCV, WNC, WPL, XDR, XTE, XTR, ZDA, ZDL, ZFO, ZTG, DBK,
  HDM, R00, PGRME)
- AIS (messages: 01, 02, 03, 04, 05, 09, 10, 11, 18, 19, 21, 24)
- SeaTalk (Raymarine device communication, aka SeaTalk1) (supported messages:
  00, 01, 05, 10, 11, 20, 21, 22, 23, 24, 25, 26, 27, 30, 36, 38, 50, 51)
- Reading data from serial ports (NMEA, SeaTalk)
- Basic geodesic functions, suitable for martime navigation.
  - Calculation of CPA and TCPA
  - Distance of two points on a sphere
  - Distance of two points on an ellipsoid using formula of Vincenty
  - Distance of two points on an ellipsoid using formula of Lambert

More documentation to be found after building it, see (some are
optimized for doxygen not github):

- [Features Overview](doc/features.md)
- [Examples](doc/examples.md)
- [Development Environment](doc/devenv.md)


Examples
--------

~~~~~~~~~~~~~{.cpp}
	using namespace marnav;

	auto sentence = nmea::make_sentence(
		"$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");
	std::cout << sentence->tag() << "\n";
	auto rmc = nmea::sentence_cast<nmea::rmc>(sentence);
	std::cout << "latitude : " << nmea::to_string(rmc->get_lat()) << "\n";
	std::cout << "longitude: " << nmea::to_string(rmc->get_lon()) << "\n";
~~~~~~~~~~~~~

~~~~~~~~~~~~~{.cpp}
	using namespace marnav;

	// received sentences
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
~~~~~~~~~~~~~

Build Documentation
-------------------

	mkdir build
	cd build
	cmake ..
	make doc


Build Library
-------------

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make


LICENSE
-------

See file [LICENSE](LICENSE)

