cmake_minimum_required(VERSION 3.2)

option(ENABLE_STATIC "Enable static library" ON)

### lib: marnav

if(${ENABLE_STATIC})
	set(LIBRARY_TYPE "STATIC")
else()
	set(LIBRARY_TYPE "SHARED")
endif()
message(STATUS "Build library type: ${LIBRARY_TYPE}")

message(STATUS "Build AIS support    : ${ENABLE_AIS}")
message(STATUS "Build SeaTalk support: ${ENABLE_SEATALK}")
message(STATUS "Build IO support     : ${ENABLE_IO}")

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/marnav/version.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/marnav/version.hpp
	)

if(MSVC)
	add_definitions(-D_USE_MATH_DEFINES)
endif()

set(SOURCES
	# intentionally left blank
	)

if(ENABLE_SEATALK)
	set(SOURCES ${SOURCES}
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
		marnav/seatalk/message_38.cpp
		marnav/seatalk/message_50.cpp
		marnav/seatalk/message_51.cpp
		marnav/seatalk/message_52.cpp
		marnav/seatalk/message_53.cpp
		marnav/seatalk/message_54.cpp
		marnav/seatalk/message_56.cpp
		marnav/seatalk/message_58.cpp
		marnav/seatalk/message_59.cpp
		marnav/seatalk/message_65.cpp
		marnav/seatalk/message_66.cpp
		marnav/seatalk/message_6c.cpp
		marnav/seatalk/message_86.cpp
		marnav/seatalk/message_87.cpp
		marnav/seatalk/message_89.cpp
		)
endif()

if(ENABLE_AIS)
	set(SOURCES ${SOURCES}
		marnav/ais/ais.cpp
		marnav/ais/angle.cpp
		marnav/ais/rate_of_turn.cpp
		marnav/ais/name.cpp
		marnav/ais/binary_data.cpp
		marnav/ais/binary_001_11.cpp
		marnav/ais/binary_200_10.cpp
		marnav/ais/message_01.cpp
		marnav/ais/message_02.cpp
		marnav/ais/message_03.cpp
		marnav/ais/message_04.cpp
		marnav/ais/message_05.cpp
		marnav/ais/message_06.cpp
		marnav/ais/message_07.cpp
		marnav/ais/message_08.cpp
		marnav/ais/message_09.cpp
		marnav/ais/message_10.cpp
		marnav/ais/message_11.cpp
		marnav/ais/message_12.cpp
		marnav/ais/message_13.cpp
		marnav/ais/message_14.cpp
		marnav/ais/message_17.cpp
		marnav/ais/message_18.cpp
		marnav/ais/message_19.cpp
		marnav/ais/message_20.cpp
		marnav/ais/message_21.cpp
		marnav/ais/message_22.cpp
		marnav/ais/message_23.cpp
		marnav/ais/message_24.cpp
		)
endif()

if(ENABLE_IO)

	if(MSVC)
		set(SOURCES ${SOURCES}
			marnav/io/win/serial.cpp
			)
	else()
		set(SOURCES ${SOURCES}
			marnav/io/serial.cpp
			)
	endif()
	set(SOURCES ${SOURCES}
		marnav/io/nmea_reader.cpp
		marnav/io/default_nmea_reader.cpp
		)

	if(ENABLE_SEATALK)
		set(SOURCES ${SOURCES}
			marnav/io/seatalk_reader.cpp
			marnav/io/default_seatalk_reader.cpp
			)
	endif()
endif()

add_library(marnav ${LIBRARY_TYPE}
	marnav/math/floatingpoint.hpp
	marnav/math/vector.hpp
	marnav/math/matrix.hpp
	marnav/math/quaternion.hpp
	marnav/utils/mmsi.cpp
	marnav/utils/mmsi_country.cpp
	marnav/geo/angle.cpp
	marnav/geo/position.cpp
	marnav/geo/region.cpp
	marnav/geo/cpa.cpp
	marnav/geo/geodesic.cpp
	marnav/nmea/waypoint.cpp
	marnav/nmea/tag_block.cpp
	marnav/nmea/talker_id.cpp
	marnav/nmea/convert.cpp
	marnav/nmea/manufacturer.cpp
	marnav/nmea/checks.cpp
	marnav/nmea/split.cpp
	marnav/nmea/angle.cpp
	marnav/nmea/string.cpp
	marnav/nmea/name.cpp
	marnav/nmea/io.cpp
	marnav/nmea/date.cpp
	marnav/nmea/time.cpp
	marnav/nmea/checksum.cpp
	marnav/nmea/sentence.cpp
	marnav/nmea/detail.cpp
	marnav/nmea/ais_helper.cpp
	marnav/nmea/nmea.cpp
	marnav/nmea/aam.cpp
	marnav/nmea/alm.cpp
	marnav/nmea/apa.cpp
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
	marnav/nmea/gbs.cpp
	marnav/nmea/gga.cpp
	marnav/nmea/glc.cpp
	marnav/nmea/gll.cpp
	marnav/nmea/gns.cpp
	marnav/nmea/grs.cpp
	marnav/nmea/gsa.cpp
	marnav/nmea/gst.cpp
	marnav/nmea/gsv.cpp
	marnav/nmea/gtd.cpp
	marnav/nmea/hdg.cpp
	marnav/nmea/hfb.cpp
	marnav/nmea/hdm.cpp
	marnav/nmea/hdt.cpp
	marnav/nmea/hsc.cpp
	marnav/nmea/its.cpp
	marnav/nmea/lcd.cpp
	marnav/nmea/msk.cpp
	marnav/nmea/mss.cpp
	marnav/nmea/mtw.cpp
	marnav/nmea/mwd.cpp
	marnav/nmea/mwv.cpp
	marnav/nmea/osd.cpp
	marnav/nmea/r00.cpp
	marnav/nmea/rma.cpp
	marnav/nmea/rmb.cpp
	marnav/nmea/rmc.cpp
	marnav/nmea/rot.cpp
	marnav/nmea/rpm.cpp
	marnav/nmea/rsa.cpp
	marnav/nmea/rsd.cpp
	marnav/nmea/rte.cpp
	marnav/nmea/sfi.cpp
	marnav/nmea/stn.cpp
	marnav/nmea/tds.cpp
	marnav/nmea/tfi.cpp
	marnav/nmea/tll.cpp
	marnav/nmea/tpc.cpp
	marnav/nmea/tpr.cpp
	marnav/nmea/tpt.cpp
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
	marnav/nmea/pgrmm.cpp
	marnav/nmea/pgrmz.cpp
	${SOURCES}
	)

include(GenerateExportHeader)

generate_export_header(marnav EXPORT_FILE_NAME "marnav/marnav_export.h")


target_include_directories(marnav
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${CMAKE_CURRENT_BINARY_DIR}
	)

if(NOT MSVC)
	target_compile_options(marnav
		PRIVATE
			-pipe
			-ggdb
			-Wall
			-Wextra
			-pedantic-errors
			-Wold-style-cast
		)
endif()

if(ENABLE_PROFILING)
	target_compile_options(marnav
		PRIVATE
			-pg
		)
endif()
if(ENABLE_BENCHMARK)
	target_compile_options(marnav
		PRIVATE
			-fno-omit-frame-pointer
		)
endif()
if(ENABLE_WARNING_HELL)
	message(STATUS "Behold: entering the hell of extended warnings")
	target_compile_options(marnav
		PRIVATE
			-Wcast-align
			-Wcast-qual
			-Werror
			-Wdisabled-optimization
			-Wfloat-equal
			-Wformat=2
			-Wformat-security
			-Wformat-y2k
			-Wimport
			-Winit-self
			-Winline
			-Wmissing-field-initializers
			-Wmissing-format-attribute
			-Wmissing-include-dirs
			-Wmissing-noreturn
			-Wnon-virtual-dtor
			-Woverloaded-virtual
			-Wpacked
			-Wpointer-arith
			-Wredundant-decls
			-Wstrict-aliasing=2
			-Wswitch
			-Wunreachable-code
			-Wunused
			-Wunused-parameter
			-Wvariadic-macros
			-Wwrite-strings
			# explicitly disabled on purpose:
			-Wno-conversion
			-Wno-shadow
			-Wno-sign-conversion
			-Wno-stack-protector
			-Wno-effc++
			-Wno-padded
			-Wno-long-long
			-Wno-unused-function
			-Wno-comment
			-Wno-format-nonliteral
			-Wno-switch-enum
			-Wno-switch-default
		)
endif()

if(ENABLE_SANITIZER)
	message(STATUS "Sanitizer: enabled")
	target_compile_options(marnav
		PRIVATE
			-fsanitize=address
			-fsanitize=undefined
		)

	target_link_libraries(marnav
		asan
		ubsan
		)
endif()

if(build_type_lower MATCHES coverage)
	message(STATUS "Coverage: enabled")
	target_compile_options(marnav
		PRIVATE
			--coverage
			-fprofile-arcs
			-ftest-coverage
			-fno-inline
			-fno-inline-small-functions
			-fno-default-inline
		)
endif()

set_target_properties(marnav
	PROPERTIES VERSION "${PROJECT_VERSION}"
	SOVERSION "${PROJECT_VERSION}"
	)

install(
	TARGETS marnav
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/marnav/version.hpp
		${CMAKE_CURRENT_BINARY_DIR}/marnav/marnav_export.h
	DESTINATION include/marnav
	)

install(
	FILES
		marnav/nmea/constants.hpp
		marnav/nmea/tag_block.hpp
		marnav/nmea/talker_id.hpp
		marnav/nmea/sentence_id.hpp
		marnav/nmea/convert.hpp
		marnav/nmea/waypoint.hpp
		marnav/nmea/manufacturer.hpp
		marnav/nmea/angle.hpp
		marnav/nmea/string.hpp
		marnav/nmea/name.hpp
		marnav/nmea/io.hpp
		marnav/nmea/date.hpp
		marnav/nmea/time.hpp
		marnav/nmea/checksum.hpp
		marnav/nmea/checksum_enum.hpp
		marnav/nmea/sentence.hpp
		marnav/nmea/detail.hpp
		marnav/nmea/ais_helper.hpp
		marnav/nmea/nmea.hpp
		marnav/nmea/aam.hpp
		marnav/nmea/alm.hpp
		marnav/nmea/apa.hpp
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
		marnav/nmea/gbs.hpp
		marnav/nmea/gga.hpp
		marnav/nmea/glc.hpp
		marnav/nmea/gll.hpp
		marnav/nmea/gns.hpp
		marnav/nmea/grs.hpp
		marnav/nmea/gsa.hpp
		marnav/nmea/gst.hpp
		marnav/nmea/gsv.hpp
		marnav/nmea/gtd.hpp
		marnav/nmea/hdg.hpp
		marnav/nmea/hfb.hpp
		marnav/nmea/hdm.hpp
		marnav/nmea/hdt.hpp
		marnav/nmea/hsc.hpp
		marnav/nmea/its.hpp
		marnav/nmea/lcd.hpp
		marnav/nmea/msk.hpp
		marnav/nmea/mss.hpp
		marnav/nmea/mtw.hpp
		marnav/nmea/mwd.hpp
		marnav/nmea/mwv.hpp
		marnav/nmea/osd.hpp
		marnav/nmea/r00.hpp
		marnav/nmea/rma.hpp
		marnav/nmea/rmb.hpp
		marnav/nmea/rmc.hpp
		marnav/nmea/rot.hpp
		marnav/nmea/rpm.hpp
		marnav/nmea/rsa.hpp
		marnav/nmea/rsd.hpp
		marnav/nmea/rte.hpp
		marnav/nmea/sfi.hpp
		marnav/nmea/stn.hpp
		marnav/nmea/tds.hpp
		marnav/nmea/tfi.hpp
		marnav/nmea/tll.hpp
		marnav/nmea/tpc.hpp
		marnav/nmea/tpr.hpp
		marnav/nmea/tpt.hpp
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

if(ENABLE_AIS)
	install(
		FILES
			marnav/ais/ais.hpp
			marnav/ais/angle.hpp
			marnav/ais/rate_of_turn.hpp
			marnav/ais/name.hpp
			marnav/ais/binary_data.hpp
			marnav/ais/binary_001_11.hpp
			marnav/ais/binary_200_10.hpp
			marnav/ais/message.hpp
			marnav/ais/message_01.hpp
			marnav/ais/message_02.hpp
			marnav/ais/message_03.hpp
			marnav/ais/message_04.hpp
			marnav/ais/message_05.hpp
			marnav/ais/message_06.hpp
			marnav/ais/message_07.hpp
			marnav/ais/message_08.hpp
			marnav/ais/message_09.hpp
			marnav/ais/message_10.hpp
			marnav/ais/message_11.hpp
			marnav/ais/message_12.hpp
			marnav/ais/message_13.hpp
			marnav/ais/message_14.hpp
			marnav/ais/message_17.hpp
			marnav/ais/message_18.hpp
			marnav/ais/message_19.hpp
			marnav/ais/message_20.hpp
			marnav/ais/message_21.hpp
			marnav/ais/message_22.hpp
			marnav/ais/message_23.hpp
			marnav/ais/message_24.hpp
		DESTINATION include/marnav/ais
		)
endif()

if(ENABLE_SEATALK)
	install(
		FILES
			marnav/seatalk/key.hpp
			marnav/seatalk/equipment.hpp
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
			marnav/seatalk/message_38.hpp
			marnav/seatalk/message_50.hpp
			marnav/seatalk/message_51.hpp
			marnav/seatalk/message_52.hpp
			marnav/seatalk/message_53.hpp
			marnav/seatalk/message_54.hpp
			marnav/seatalk/message_56.hpp
			marnav/seatalk/message_58.hpp
			marnav/seatalk/message_59.hpp
			marnav/seatalk/message_65.hpp
			marnav/seatalk/message_66.hpp
			marnav/seatalk/message_6c.hpp
			marnav/seatalk/message_86.hpp
			marnav/seatalk/message_87.hpp
			marnav/seatalk/message_89.hpp
		DESTINATION include/marnav/seatalk
		)
endif()

install(
	FILES
		marnav/utils/unused.hpp
		marnav/utils/unique.hpp
		marnav/utils/bitset.hpp
		marnav/utils/bitset_string.hpp
		marnav/utils/optional.hpp
		marnav/utils/mmsi.hpp
		marnav/utils/mmsi_country.hpp
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

if(ENABLE_IO)
	install(
		FILES
			marnav/io/device.hpp
			marnav/io/serial.hpp
			marnav/io/nmea_reader.hpp
			marnav/io/default_nmea_reader.hpp
			marnav/io/default_nmea_serial.hpp
		DESTINATION include/marnav/io
		)
	if(ENABLE_SEATALK)
		install(
			FILES
				marnav/io/seatalk_reader.hpp
				marnav/io/default_seatalk_reader.hpp
				marnav/io/default_seatalk_serial.hpp
			DESTINATION include/marnav/io
			)
	endif()
endif()

# stuff for the config and config-version files
set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib)
include(CMakePackageConfigHelpers)
configure_package_config_file(
	config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	INSTALL_DESTINATION "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}"
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
		"${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}"
	)


message(STATUS "Build Tools: ${ENABLE_TOOLS}")
if(ENABLE_TOOLS)
	### bin: nmeasum
	add_executable(nmeasum
		nmeasum.cpp
		)

	target_include_directories(nmeasum
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}
			${CMAKE_CURRENT_BINARY_DIR}
		)

	if(NOT MSVC)
		target_compile_options(nmeasum
			PRIVATE
				-pipe
				-ggdb
				-Wall
				-Wextra
				-pedantic-errors
			)
	endif()

	### bin: nmeadump
	if(ENABLE_AIS AND ENABLE_IO)
		add_executable(nmeadump
			nmeadump.cpp
			)

		target_include_directories(nmeadump
			PRIVATE
				${CMAKE_CURRENT_SOURCE_DIR}
				${CMAKE_CURRENT_SOURCE_DIR}/../extern
			)

		if(NOT MSVC)
			target_compile_options(nmeadump
				PRIVATE
					-pipe
					-ggdb
					-Wall
					-Wextra
					-pedantic-errors
				)
		endif()

		target_link_libraries(nmeadump
			marnav
			)
	endif()
endif()
