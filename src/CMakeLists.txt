cmake_minimum_required(VERSION 2.8)
project(nmea)

option(ENABLE_STATIC
	"Enable static library" ON)

set(SOURCE_UTILS
	utils/unique.hpp
	utils/bitset.hpp
	)

set(SOURCE_GEO
	geo/angle.cpp
	)

set(SOURCE_NMEA_0183
	nmea/angle.cpp
	nmea/date.cpp
	nmea/time.cpp
	nmea/sentence.cpp
	nmea/nmea.cpp
	nmea/aam.cpp
	nmea/bod.cpp
	nmea/dbt.cpp
	nmea/dpt.cpp
	nmea/gga.cpp
	nmea/gll.cpp
	nmea/gsa.cpp
	nmea/gsv.cpp
	nmea/hdg.cpp
	nmea/mtw.cpp
	nmea/mwv.cpp
	nmea/rmb.cpp
	nmea/rmc.cpp
	nmea/rte.cpp
	nmea/vhw.cpp
	nmea/vlw.cpp
	nmea/vtg.cpp
	nmea/vwr.cpp
	nmea/vdm.cpp
	nmea/vdo.cpp
	nmea/optional.hpp
	)

set(SOURCE_AIS
	ais/ais.cpp
	ais/message.cpp
	ais/message_01.cpp
	ais/message_02.cpp
	ais/message_03.cpp
	ais/message_05.cpp
	)

set(SOURCE_SEATALK
	seatalk/seatalk.cpp
	seatalk/message.cpp
	seatalk/message_00.cpp
	seatalk/message_01.cpp
	seatalk/message_10.cpp
	seatalk/message_11.cpp
	seatalk/message_20.cpp
	seatalk/message_21.cpp
	seatalk/message_22.cpp
	seatalk/message_23.cpp
	seatalk/message_25.cpp
	seatalk/message_27.cpp
	)

add_executable(nmeasum
	nmeasum.cpp
	)

if(${ENABLE_STATIC})
	set(LIBRARY_TYPE "STATIC")
else()
	set(LIBRARY_TYPE "SHARED")
endif()
message(STATUS "Build library type: ${LIBRARY_TYPE}")

add_library(marnav ${LIBRARY_TYPE}
	${SOURCE_UTILS}
	${SOURCE_GEO}
	${SOURCE_NMEA_0183}
	${SOURCE_AIS}
	${SOURCE_SEATALK}
	)

set_target_properties(marnav
	PROPERTIES VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"
	SOVERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}"
	)

install(
	TARGETS marnav
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	FILES
		nmea/angle.hpp
		nmea/io.hpp
		nmea/date.hpp
		nmea/time.hpp
		nmea/optional.hpp
		nmea/sentence.hpp
		nmea/nmea.hpp
		nmea/aam.hpp
		nmea/bod.hpp
		nmea/dbt.hpp
		nmea/dpt.hpp
		nmea/gga.hpp
		nmea/gll.hpp
		nmea/gsa.hpp
		nmea/gsv.hpp
		nmea/mtw.hpp
		nmea/rmb.hpp
		nmea/rmc.hpp
		nmea/rte.hpp
		nmea/vtg.hpp
		nmea/vwr.hpp
		nmea/vdm.hpp
		nmea/vdo.hpp
	DESTINATION include/marnav/nmea
	)

install(
	FILES
		ais/ais.hpp
		ais/message.hpp
		ais/message_01.hpp
		ais/message_02.hpp
		ais/message_03.hpp
		ais/message_05.hpp
	DESTINATION include/marnav/ais
	)

install(
	FILES
		seatalk/seatalk.hpp
		seatalk/message.hpp
		seatalk/message_00.hpp
		seatalk/message_01.hpp
		seatalk/message_10.hpp
		seatalk/message_11.hpp
		seatalk/message_20.hpp
		seatalk/message_21.hpp
		seatalk/message_22.hpp
		seatalk/message_23.hpp
		seatalk/message_25.hpp
		seatalk/message_27.hpp
	DESTINATION include/marnav/seatalk
	)

install(
	FILES
		utils/unique.hpp
		utils/bitset.hpp
	DESTINATION include/marnav/utils
	)

install(
	FILES
		geo/angle.hpp
	DESTINATION include/marnav/geo
	)

