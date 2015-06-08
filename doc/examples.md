Examples {#page_examples}
========

[TOC]

NMEA {#sec_nmea}
====

Parse a NMEA sentence {#sec_nmea_parse}
---------------------

~~~~~~~~~~~~~{.cpp}
	auto sentence = nmea::make_sentence(
		"$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");
	std::cout << sentence->tag() << "\n";
	auto rmc = nmea::sentence_cast<nmea::rmc>(sentence);
	std::cout << "latitude : " << nmea::to_string(rmc->get_lat()) << "\n";
	std::cout << "longitude: " << nmea::to_string(rmc->get_lon()) << "\n";
~~~~~~~~~~~~~


Write a NMEA sentence {#sec_nmea_write}
---------------------

~~~~~~~~~~~~~{.cpp}
	nmea::mtw mtw;
	mtw.set_temperature(22.5);
	std::string data = nmea::to_string(mtw);
~~~~~~~~~~~~~

AIS {#sec_ais}
===

Process AIS related NMEA messages {#sec_ais_read}
---------------------------------

~~~~~~~~~~~~~{.cpp}
	// collect NMEA data of all fragments, from whatever source
	std::vector<std::unique_ptr<nmea::sentence>> v;
	v.push_back(nmea::make_sentence("!AIVDM,1,1,,B,177KQJ5000G?tO`K>RA1wUbN0TKH,0*5C"));

	// collect payload from all fragments
	auto payload = nmea::collect_payload(v.begin(), v.end());

	// make AIS message from payload
	auto msg = ais::make_message(payload);

	// process concrete AIS message
	auto pos_report = ais::message_cast<ais::message_01>(msg);
	auto mmsi = pos_report->get_mmsi();
~~~~~~~~~~~~~


Create NMEA sentences from AIS data {#sec_ais_create}
-----------------------------------
\includelineno examples/create_nmea_from_ais.cpp

Utils {#sec_utils}
=====

Iterate through a bitset {#sec_utils_bitset_iterate}
------------------------
\includelineno examples/bitset_iterate.cpp

Complete examples {#sec_complete}
=================

All those examples are to be found in the directory `examples`.

Parse NMEA from a string {#sec_file_parse_nmea}
------------------------
\includelineno examples/parse_nmea.cpp

Read NMEA from serial port {#sec_file_read_nmea}
--------------------------
\includelineno examples/read_nmea.cpp

Read NMEA from serial port using Boost.ASIO {#sec_file_read_nmea_boostasio}
-------------------------------------------
\includelineno examples/read_nmea_boostasio.cpp

Read SeaTalk from serial port {#sec_file_read_seatalk}
-----------------------------
\includelineno examples/read_seatalk.cpp

Read AIS data from string {#sec_file_read_ais}
-------------------------
\includelineno examples/read_ais.cpp

Run a NMEA multiplexer {#sec_file_nmea_multiplexer}
----------------------
\includelineno examples/nmea_multiplexer.cpp

Using select with marnav::io::device {#sec_file_select}
------------------------------------
\includelineno examples/select.cpp

Simple SeaTalk to NMEA converter {#sec_file_seatalk_to_nmea}
--------------------------------
\includelineno examples/simple_seatalk_nmea_converter.cpp

