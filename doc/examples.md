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

Example 1:
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

Example 2:
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

Qt5 GUI application reading NMEA {#sec_file_qt5}
--------------------------------
\includelineno examples/qtnmeadiag/main.cpp
\includelineno examples/qtnmeadiag/MainWindow.hpp
\includelineno examples/qtnmeadiag/MainWindow.cpp

Simple NMEA receiver and forward to a TCP server {#sec_file_tcp_forward}
------------------------------------------------
\includelineno examples/serial_to_tcp.cpp

Library {#sec_lib}
=======

Using the library in a cmake environment {#sec_lib_cmake}
----------------------------------------
If you are using this library within a cmake environment, you might
want to use ``find_package``.

Build and install the library:
~~~~~~~~~~~~~
	mkdir build
	cd build
	mkdir local
	cmake -DCMAKE_INSTALL_PREFIX=`pwd`/local ..
	make
	make install
~~~~~~~~~~~~~

Now the installation of the library is in the directory ``marnav/build/local``.

To build the test program:
~~~~~~~~~~~~~
	cd build
	export marnav_DIR=`pwd`/local
	mkdir test
	cd test
	cmake ../../example/library
	make
	./foobar
~~~~~~~~~~~~~

The ``export`` is necessary because cmake would not find the necessary
configuration of the library, which is installed in ``.../lib/marnav/cmake``.

The tarball also contains the configuration files:
~~~~~~~~~~~~~
	tar -xf marnav-0.3.1-Linux.tar.gz
	export marnav_DIR=`pwd`/marnav-0.3.1-Linux
	mkdir test
	cd test
	cmake ../../example/library
	make
	./foobar
~~~~~~~~~~~~~

You might want to consider extending the cmake modules path (in your
``CMakeLists.txt``) accordingly.

