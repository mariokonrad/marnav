cmake_minimum_required(VERSION 2.8)

option(ENABLE_STATIC
	"Enable static library" ON)

set(SOURCE_UTILS
	marnav/utils/unique.hpp
	marnav/utils/bitset.hpp
	marnav/utils/optional.hpp
	)

set(SOURCE_GEO
	marnav/geo/angle.cpp
	)

set(SOURCE_NMEA_0183
	marnav/nmea/constants.cpp
	marnav/nmea/angle.cpp
	marnav/nmea/date.cpp
	marnav/nmea/time.cpp
	marnav/nmea/sentence.cpp
	marnav/nmea/nmea.cpp
	marnav/nmea/aam.cpp
	marnav/nmea/bod.cpp
	marnav/nmea/dbt.cpp
	marnav/nmea/dpt.cpp
	marnav/nmea/gga.cpp
	marnav/nmea/gll.cpp
	marnav/nmea/gsa.cpp
	marnav/nmea/gsv.cpp
	marnav/nmea/hdg.cpp
	marnav/nmea/mtw.cpp
	marnav/nmea/mwv.cpp
	marnav/nmea/rmb.cpp
	marnav/nmea/rmc.cpp
	marnav/nmea/rte.cpp
	marnav/nmea/vhw.cpp
	marnav/nmea/vlw.cpp
	marnav/nmea/vtg.cpp
	marnav/nmea/vwr.cpp
	marnav/nmea/vdm.cpp
	marnav/nmea/vdo.cpp
	)

set(SOURCE_AIS
	marnav/ais/ais.cpp
	marnav/ais/message.cpp
	marnav/ais/message_01.cpp
	marnav/ais/message_02.cpp
	marnav/ais/message_03.cpp
	marnav/ais/message_05.cpp
	)

set(SOURCE_SEATALK
	marnav/seatalk/seatalk.cpp
	marnav/seatalk/message.cpp
	marnav/seatalk/message_00.cpp
	marnav/seatalk/message_01.cpp
	marnav/seatalk/message_10.cpp
	marnav/seatalk/message_11.cpp
	marnav/seatalk/message_20.cpp
	marnav/seatalk/message_21.cpp
	marnav/seatalk/message_22.cpp
	marnav/seatalk/message_23.cpp
	marnav/seatalk/message_25.cpp
	marnav/seatalk/message_27.cpp
	)

set(SOURCE_IO
	marnav/io/serial.cpp
	marnav/io/seatalk_serial.cpp
	marnav/io/nmea_serial.cpp
	marnav/io/default_nmea_reader.cpp
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
	${SOURCE_IO}
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
		marnav/nmea/constants.hpp
		marnav/nmea/angle.hpp
		marnav/nmea/io.hpp
		marnav/nmea/date.hpp
		marnav/nmea/time.hpp
		marnav/nmea/sentence.hpp
		marnav/nmea/nmea.hpp
		marnav/nmea/aam.hpp
		marnav/nmea/bod.hpp
		marnav/nmea/dbt.hpp
		marnav/nmea/dpt.hpp
		marnav/nmea/gga.hpp
		marnav/nmea/gll.hpp
		marnav/nmea/gsa.hpp
		marnav/nmea/gsv.hpp
		marnav/nmea/mtw.hpp
		marnav/nmea/rmb.hpp
		marnav/nmea/rmc.hpp
		marnav/nmea/rte.hpp
		marnav/nmea/vtg.hpp
		marnav/nmea/vwr.hpp
		marnav/nmea/vdm.hpp
		marnav/nmea/vdo.hpp
	DESTINATION include/marnav/nmea
	)

install(
	FILES
		marnav/ais/ais.hpp
		marnav/ais/message.hpp
		marnav/ais/message_01.hpp
		marnav/ais/message_02.hpp
		marnav/ais/message_03.hpp
		marnav/ais/message_05.hpp
	DESTINATION include/marnav/ais
	)

install(
	FILES
		marnav/seatalk/seatalk.hpp
		marnav/seatalk/message.hpp
		marnav/seatalk/message_00.hpp
		marnav/seatalk/message_01.hpp
		marnav/seatalk/message_10.hpp
		marnav/seatalk/message_11.hpp
		marnav/seatalk/message_20.hpp
		marnav/seatalk/message_21.hpp
		marnav/seatalk/message_22.hpp
		marnav/seatalk/message_23.hpp
		marnav/seatalk/message_25.hpp
		marnav/seatalk/message_27.hpp
	DESTINATION include/marnav/seatalk
	)

install(
	FILES
		marnav/utils/unique.hpp
		marnav/utils/bitset.hpp
		marnav/utils/optional.hpp
	DESTINATION include/marnav/utils
	)

install(
	FILES
		marnav/geo/angle.hpp
	DESTINATION include/marnav/geo
	)

install(
	FILES
		marnav/io/device.hpp
		marnav/io/serial.hpp
		marnav/io/seatalk_serial.hpp
		marnav/io/nmea_serial.hpp
		marnav/io/default_nmea_reader.hpp
	DESTINATION include/marnav/io
	)

