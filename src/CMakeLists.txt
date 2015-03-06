cmake_minimum_required(VERSION 2.8)
project(nmea)

add_library(nmea
	nmea/angle.cpp
	nmea/date.cpp
	nmea/time.cpp
	nmea/sentence.cpp
	nmea/nmea.cpp
	nmea/dbt.cpp
	nmea/gll.cpp
	nmea/mtw.cpp
	nmea/rmc.cpp
	nmea/optional.hpp
	nmea/unique.hpp
	)

set_target_properties(nmea
	PROPERTIES VERSION 0.0.1
	SOVERSION 0.0.1
	)

install(
	TARGETS nmea
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	FILES
		nmea/angle.hpp
		nmea/date.hpp
		nmea/time.hpp
		nmea/optional.hpp
		nmea/sentence.hpp
		nmea/unique.hpp
		nmea/nmea.hpp
		nmea/dbt.hpp
		nmea/gll.hpp
		nmea/mtw.hpp
		nmea/rmc.hpp
	DESTINATION include/nmea
	)

