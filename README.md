libmarnav
=========

Copyright (c) 2015, Mario Konrad "mario.konrad@gmx.net"

This is a C++11 library for maritime navigation purposes.

It supports (partially):
- NMEA-0183
- AIS
- SeaTalk (Raymarine device communication)

Supported sentences for NMEA-0183 (read and write):
- AAM
- BOD
- DBT
- DPT
- GGA
- GLL
- GSA
- GSV
- HDG
- MTW
- MWV
- RMB
- RMC
- RTE
- VHW
- VLW
- VTG
- VWR
- VDM
- VDO

Supported messages for AIS (decode and encode):
- type 1: position report class A
- type 2: position report class A (assigned schedule)
- type 3: position report class A (response to interrogation)
- type 5: static and voyage related data

Suported messages for SeaTalk (decode and encode):
- type 00: depth below transducer
- type 01: equipment id
- type 10: apparent wind angle
- type 11: apparent wind speed
- type 20: speed through water
- type 21: trip mileage
- type 22: total mileage
- type 27: water temperature 2


EXAMPLES
--------

Parse a NMEA sentence:

	auto sentence = nmea::make_sentence(
		"$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");
	std::cout << s->tag() << "\n";
	auto rmc = nmea::sentence_cast<nmea::rmc>(sentence);
	std::cout << "latitude : " << nmea::to_string(rmc->lat()) << "\n";
	std::cout << "longitude: " << nmea::to_string(rmc->lon()) << "\n";


Write a NMEA sentence:

	nmea::mtw mtw;
	mtw.set_temperature(22.5);
	std::string data = nmea::to_string(mtw);


Process AIS related NMEA messages:

	// collect NMEA data of all fragments, from whatever source
	std::vector<nmea::vdm> v;
	v.push_back(
		nmea::sentence_cast<nmea::vdm>(
			nmea::make_sentence("!AIVDM,1,1,,B,177KQJ5000G?tO`K>RA1wUbN0TKH,0*5C")));

	// collect payload from all fragments
	auto payload = nmea::collect_payload(v.begin(), v.end());

	// make AIS message from payload
	auto msg = ais::make_message(payload);

	// process concrete AIS message
	auto pos_report = ais::message_cast<ais::message_01>(msg);
	auto mmsi = pos_report->get_mmsi();


Create NMEA sentences from AIS data:

	// prepare AIS data
	ais::message_01 pos_report;
	pos_report.set_sog(82);
	// ... most data not shown here

	// create payload
	auto payload = ais::encode_message(pos_report);

	// create NMEA sentences
	uint32_t fragment = 1;
	for (const auto& p : payload) {
		nmea::vdm vdm;
		vdm.set_n_fragments(payload.size());
		vdm.set_fragment(fragment);
		vdm.set_radio_channel(nmea::ais_channel::B);
		vdm.set_payload(p);
		++fragment;

		// collect, send or do something with the sentence...
		std::string s = nmea::to_string(vdm);
		// ...
	}


GOALS
-----

There are already implementaions for reading and writing NMEA-0183 or AIS.
The goal of this library is
- to have an implementation in modern C++
- easy to use API
- unit tested
- trivial integration into projects

REQUIREMENTS
------------

Tools needed to build the library:
- GCC 4.9.2 or newer
- cmake 2.8.11 or newer
- clang-format 3.4 or newer

optional (somewhat):
- lcov / genhtml
- doxygen
- cppcheck

There are no other dependencies despite the standard library (C++11)
to build this library.

Other compilers may work, however untested.

BUILD
-----

For normal, debug and release builds use the standard cmake CMAKE_BUILD_TYPE variable.
For example a debug build:

Debug build:

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make

If you like to perform code coverage using the unit tests, do:

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Coverage ..
	make
	make coverage

LICENSE
-------

See file ```LICENSE.md```

LINKS
-----

- http://www.catb.org/gpsd/NMEA.html
- http://www.catb.org/gpsd/AIVDM.html
- http://thomasknauf.de/seatalk.htm

