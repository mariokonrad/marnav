marnav
======

[![Build Status](https://travis-ci.org/mariokonrad/marnav.svg?branch=master)](https://travis-ci.org/mariokonrad/marnav)


Copyright (c) 2015, Mario Konrad "mario.konrad@gmx.net"

This is a C++11 library for MARitime NAVigation purposes.

It supports (partially):
- NMEA-0183 (sentences: AAM, ALM, APB, BOD, BWC, BWR, BWW, DBT, DPT, DSC, DSE, DTM, FSI,
  GGA, GLL, GNS, GSA, GSV, HDG, HSC, MTW, MWD, MWV, OSD, RMA, RMB, RMC, ROT, RSA, RTE, SFI,
  TLL, TTM, VBW, VDM, VDO, VDR, VHW, VLW, VTG, VWR, VPW, WCV, WNC, WPL, XDR, XTE, XTR, ZDA,
  ZDL, ZFO, ZTG, DBK, HDM, R00, PGRME)
- AIS (messages: 01, 02, 03, 04, 05, 09, 10, 11, 18, 19, 21, 24)
- SeaTalk (Raymarine device communication, aka SeaTalk1) (supported messages:
  00, 01, 05, 10, 11, 20, 21, 22, 23, 24, 25, 26, 27, 30, 36, 38)
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


Example
-------

~~~~~~~~~~~~~{.cpp}
	auto sentence = nmea::make_sentence(
		"$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");
	std::cout << sentence->tag() << "\n";
	auto rmc = nmea::sentence_cast<nmea::rmc>(sentence);
	std::cout << "latitude : " << nmea::to_string(rmc->get_lat()) << "\n";
	std::cout << "longitude: " << nmea::to_string(rmc->get_lon()) << "\n";
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

