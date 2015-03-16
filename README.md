NMEA
====

Copyright (c) 2015, Mario Konrad "mario.konrad@gmx.net"

This is a C++11 library to read and write NMEA-0183 sentences.

Supported sentences:
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

EXAMPLES
--------

Parse a sentence:

	auto sentence = nmea::make_sentence("$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");
	std::cout << s->tag() << "\n";
	auto rmc = nmea::sentence_cast<nmea::rmc>(sentence);
	std::cout << "latitude : " << rmc->lat() << "\n";
	std::cout << "longitude: " << rmc->lon() << "\n";

GOALS
-----

There are already implementaions for reading and writing NMEA-0183.
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

There are no other dependencies despite the standard library (C++11)
to build this library.

Other compilers may work, however untested.

LICENSE
-------

See file ```LICENSE.md```

