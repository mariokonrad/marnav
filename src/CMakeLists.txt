cmake_minimum_required(VERSION 3.0)

option(ENABLE_STATIC
	"Enable static library" ON)

set(SOURCE_UTILS
	marnav/utils/unique.hpp
	marnav/utils/bitset.hpp
	marnav/utils/optional.hpp
	marnav/utils/mmsi.hpp
	)

set(SOURCE_MATH
	marnav/math/floatingpoint.hpp
	marnav/math/vector.hpp
	marnav/math/matrix.hpp
	marnav/math/quaternion.hpp
	)

set(SOURCE_GEO
	marnav/geo/angle.cpp
	marnav/geo/position.cpp
	marnav/geo/region.cpp
	marnav/geo/cpa.cpp
	marnav/geo/geodesic.cpp
	)

set(SOURCE_NMEA_0183
	marnav/nmea/constants.cpp
	marnav/nmea/checks.cpp
	marnav/nmea/angle.cpp
	marnav/nmea/io.cpp
	marnav/nmea/date.cpp
	marnav/nmea/time.cpp
	marnav/nmea/sentence.cpp
	marnav/nmea/nmea.cpp
	marnav/nmea/aam.cpp
	marnav/nmea/alm.cpp
	marnav/nmea/apb.cpp
	marnav/nmea/bod.cpp
	marnav/nmea/bwc.cpp
	marnav/nmea/bww.cpp
	marnav/nmea/bwr.cpp
	marnav/nmea/dbk.cpp
	marnav/nmea/dbt.cpp
	marnav/nmea/dpt.cpp
	marnav/nmea/dsc.cpp
	marnav/nmea/dse.cpp
	marnav/nmea/dtm.cpp
	marnav/nmea/fsi.cpp
	marnav/nmea/gga.cpp
	marnav/nmea/gll.cpp
	marnav/nmea/gns.cpp
	marnav/nmea/gsa.cpp
	marnav/nmea/gsv.cpp
	marnav/nmea/hdg.cpp
	marnav/nmea/hdm.cpp
	marnav/nmea/hsc.cpp
	marnav/nmea/mtw.cpp
	marnav/nmea/mwd.cpp
	marnav/nmea/mwv.cpp
	marnav/nmea/osd.cpp
	marnav/nmea/r00.cpp
	marnav/nmea/rma.cpp
	marnav/nmea/rmb.cpp
	marnav/nmea/rmc.cpp
	marnav/nmea/rot.cpp
	marnav/nmea/rsa.cpp
	marnav/nmea/rte.cpp
	marnav/nmea/sfi.cpp
	marnav/nmea/tll.cpp
	marnav/nmea/ttm.cpp
	marnav/nmea/vbw.cpp
	marnav/nmea/vdm.cpp
	marnav/nmea/vdo.cpp
	marnav/nmea/vdr.cpp
	marnav/nmea/vhw.cpp
	marnav/nmea/vlw.cpp
	marnav/nmea/vpw.cpp
	marnav/nmea/vtg.cpp
	marnav/nmea/vwr.cpp
	marnav/nmea/wcv.cpp
	marnav/nmea/wnc.cpp
	marnav/nmea/wpl.cpp
	marnav/nmea/xdr.cpp
	marnav/nmea/xte.cpp
	marnav/nmea/xtr.cpp
	marnav/nmea/zda.cpp
	marnav/nmea/zdl.cpp
	marnav/nmea/zfo.cpp
	marnav/nmea/ztg.cpp
	marnav/nmea/pgrme.cpp
	)

set(SOURCE_AIS
	marnav/ais/ais.cpp
	marnav/ais/angle.cpp
	marnav/ais/message.cpp
	marnav/ais/message_01.cpp
	marnav/ais/message_02.cpp
	marnav/ais/message_03.cpp
	marnav/ais/message_04.cpp
	marnav/ais/message_05.cpp
	marnav/ais/message_09.cpp
	marnav/ais/message_10.cpp
	marnav/ais/message_11.cpp
	marnav/ais/message_18.cpp
	marnav/ais/message_19.cpp
	marnav/ais/message_21.cpp
	marnav/ais/message_24.cpp
	)

set(SOURCE_SEATALK
	marnav/seatalk/seatalk.cpp
	marnav/seatalk/message.cpp
	marnav/seatalk/message_00.cpp
	marnav/seatalk/message_01.cpp
	marnav/seatalk/message_05.cpp
	marnav/seatalk/message_10.cpp
	marnav/seatalk/message_11.cpp
	marnav/seatalk/message_20.cpp
	marnav/seatalk/message_21.cpp
	marnav/seatalk/message_22.cpp
	marnav/seatalk/message_23.cpp
	marnav/seatalk/message_24.cpp
	marnav/seatalk/message_25.cpp
	marnav/seatalk/message_26.cpp
	marnav/seatalk/message_27.cpp
	marnav/seatalk/message_30.cpp
	marnav/seatalk/message_36.cpp
	)

set(SOURCE_IO
	marnav/io/serial.cpp
	marnav/io/seatalk_reader.cpp
	marnav/io/nmea_reader.cpp
	marnav/io/default_nmea_reader.cpp
	marnav/io/default_seatalk_reader.cpp
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

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/marnav/version.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/marnav/version.hpp
	)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(marnav ${LIBRARY_TYPE}
	${SOURCE_UTILS}
	${SOURCE_MATH}
	${SOURCE_GEO}
	${SOURCE_NMEA_0183}
	${SOURCE_AIS}
	${SOURCE_SEATALK}
	${SOURCE_IO}
	)

set_target_properties(marnav
	PROPERTIES VERSION "${PROJECT_VERSION}"
	SOVERSION "${PROJECT_VERSION}"
	)

install(
	TARGETS marnav
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/marnav/version.hpp
	DESTINATION include/marnav
	)

install(
	FILES
		marnav/nmea/constants.hpp
		marnav/nmea/manufacturer.hpp
		marnav/nmea/checks.hpp
		marnav/nmea/angle.hpp
		marnav/nmea/io.hpp
		marnav/nmea/date.hpp
		marnav/nmea/time.hpp
		marnav/nmea/sentence.hpp
		marnav/nmea/nmea.hpp
		marnav/nmea/aam.hpp
		marnav/nmea/alm.hpp
		marnav/nmea/apb.hpp
		marnav/nmea/bod.hpp
		marnav/nmea/bwc.hpp
		marnav/nmea/bww.hpp
		marnav/nmea/bwr.hpp
		marnav/nmea/dbk.hpp
		marnav/nmea/dbt.hpp
		marnav/nmea/dpt.hpp
		marnav/nmea/dsc.hpp
		marnav/nmea/dse.hpp
		marnav/nmea/dtm.hpp
		marnav/nmea/fsi.hpp
		marnav/nmea/gga.hpp
		marnav/nmea/gll.hpp
		marnav/nmea/gns.hpp
		marnav/nmea/gsa.hpp
		marnav/nmea/gsv.hpp
		marnav/nmea/hdg.hpp
		marnav/nmea/hdm.hpp
		marnav/nmea/hsc.hpp
		marnav/nmea/mtw.hpp
		marnav/nmea/mwd.hpp
		marnav/nmea/mwv.hpp
		marnav/nmea/osd.hpp
		marnav/nmea/r00.hpp
		marnav/nmea/rma.hpp
		marnav/nmea/rmb.hpp
		marnav/nmea/rmc.hpp
		marnav/nmea/rot.hpp
		marnav/nmea/rsa.hpp
		marnav/nmea/rte.hpp
		marnav/nmea/sfi.hpp
		marnav/nmea/tll.hpp
		marnav/nmea/ttm.hpp
		marnav/nmea/vbw.hpp
		marnav/nmea/vdm.hpp
		marnav/nmea/vdo.hpp
		marnav/nmea/vdr.hpp
		marnav/nmea/vhw.hpp
		marnav/nmea/vlw.hpp
		marnav/nmea/vpw.hpp
		marnav/nmea/vtg.hpp
		marnav/nmea/vwr.hpp
		marnav/nmea/wcv.hpp
		marnav/nmea/wnc.hpp
		marnav/nmea/wpl.hpp
		marnav/nmea/xdr.hpp
		marnav/nmea/xte.hpp
		marnav/nmea/xtr.hpp
		marnav/nmea/zda.hpp
		marnav/nmea/zdl.hpp
		marnav/nmea/zfo.hpp
		marnav/nmea/ztg.hpp
		marnav/nmea/pgrme.hpp
	DESTINATION include/marnav/nmea
	)

install(
	FILES
		marnav/ais/ais.hpp
		marnav/ais/angle.hpp
		marnav/ais/message.hpp
		marnav/ais/message_01.hpp
		marnav/ais/message_02.hpp
		marnav/ais/message_03.hpp
		marnav/ais/message_04.hpp
		marnav/ais/message_05.hpp
		marnav/ais/message_09.hpp
		marnav/ais/message_10.hpp
		marnav/ais/message_11.hpp
		marnav/ais/message_18.hpp
		marnav/ais/message_19.hpp
		marnav/ais/message_21.hpp
		marnav/ais/message_24.hpp
	DESTINATION include/marnav/ais
	)

install(
	FILES
		marnav/seatalk/seatalk.hpp
		marnav/seatalk/message.hpp
		marnav/seatalk/message_00.hpp
		marnav/seatalk/message_01.hpp
		marnav/seatalk/message_05.hpp
		marnav/seatalk/message_10.hpp
		marnav/seatalk/message_11.hpp
		marnav/seatalk/message_20.hpp
		marnav/seatalk/message_21.hpp
		marnav/seatalk/message_22.hpp
		marnav/seatalk/message_23.hpp
		marnav/seatalk/message_24.hpp
		marnav/seatalk/message_25.hpp
		marnav/seatalk/message_26.hpp
		marnav/seatalk/message_27.hpp
		marnav/seatalk/message_30.hpp
		marnav/seatalk/message_36.hpp
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
		marnav/math/floatingpoint.hpp
		marnav/math/vector.hpp
		marnav/math/matrix.hpp
		marnav/math/quaternion.hpp
	DESTINATION include/marnav/math
	)

install(
	FILES
		marnav/geo/angle.hpp
		marnav/geo/position.hpp
		marnav/geo/region.hpp
		marnav/geo/cpa.hpp
		marnav/geo/geodesic.hpp
	DESTINATION include/marnav/geo
	)

install(
	FILES
		marnav/io/device.hpp
		marnav/io/serial.hpp
		marnav/io/seatalk_reader.hpp
		marnav/io/nmea_reader.hpp
		marnav/io/default_nmea_reader.hpp
		marnav/io/default_nmea_serial.hpp
		marnav/io/default_seatalk_reader.hpp
		marnav/io/default_seatalk_serial.hpp
	DESTINATION include/marnav/io
	)

# stuff for the config and config-versionn files
set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib)
include(CMakePackageConfigHelpers)
configure_package_config_file(
	config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/marnav-config.cmake"
	INSTALL_DESTINATION "${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake"
	PATH_VARS INCLUDE_INSTALL_DIR
	)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	VERSION "${PROJECT_VERSION}"
	COMPATIBILITY SameMajorVersion)
install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	DESTINATION
		"${LIB_INSTALL_DIR}/${PROJECT_NAME}/cmake"
	)


