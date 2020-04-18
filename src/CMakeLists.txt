cmake_minimum_required(VERSION 3.11)

### lib: marnav

message(STATUS "Build shared library : ${BUILD_SHARED_LIBS}")
message(STATUS "Build IO support     : ${ENABLE_IO}")
message(STATUS "Build Tools          : ${ENABLE_TOOLS}")

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/marnav/version.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/marnav/version.hpp
	)

install(
	FILES ${CMAKE_CURRENT_BINARY_DIR}/marnav/version.hpp
	DESTINATION include/marnav
	)

add_library(marnav ${LIBRARY_TYPE})
add_library(marnav::marnav ALIAS marnav)

target_compile_features(marnav
	PRIVATE
		cxx_std_11
	)

target_sources(marnav
	PRIVATE
		marnav/ais/ais.cpp
		marnav/ais/angle.cpp
		marnav/ais/binary_001_11.cpp
		marnav/ais/binary_200_10.cpp
		marnav/ais/binary_data.cpp
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
		marnav/ais/name.cpp
		marnav/ais/rate_of_turn.cpp
		marnav/ais/vessel_dimension.cpp
		marnav/geo/angle.cpp
		marnav/geo/cpa.cpp
		marnav/geo/geodesic.cpp
		marnav/geo/position.cpp
		marnav/geo/region.cpp
		marnav/nmea/aam.cpp
		marnav/nmea/ais_helper.cpp
		marnav/nmea/alm.cpp
		marnav/nmea/angle.cpp
		marnav/nmea/apa.cpp
		marnav/nmea/apb.cpp
		marnav/nmea/bec.cpp
		marnav/nmea/bod.cpp
		marnav/nmea/bwc.cpp
		marnav/nmea/bwr.cpp
		marnav/nmea/bww.cpp
		marnav/nmea/checks.cpp
		marnav/nmea/checksum.cpp
		marnav/nmea/convert.cpp
		marnav/nmea/date.cpp
		marnav/nmea/dbk.cpp
		marnav/nmea/dbt.cpp
		marnav/nmea/detail.cpp
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
		marnav/nmea/hdm.cpp
		marnav/nmea/hdt.cpp
		marnav/nmea/hex_digit.hpp
		marnav/nmea/hfb.cpp
		marnav/nmea/hsc.cpp
		marnav/nmea/io.cpp
		marnav/nmea/its.cpp
		marnav/nmea/lcd.cpp
		marnav/nmea/manufacturer.cpp
		marnav/nmea/mob.cpp
		marnav/nmea/msk.cpp
		marnav/nmea/mss.cpp
		marnav/nmea/mtw.cpp
		marnav/nmea/mwd.cpp
		marnav/nmea/mwv.cpp
		marnav/nmea/name.cpp
		marnav/nmea/nmea.cpp
		marnav/nmea/osd.cpp
		marnav/nmea/pgrme.cpp
		marnav/nmea/pgrmm.cpp
		marnav/nmea/pgrmz.cpp
		marnav/nmea/r00.cpp
		marnav/nmea/rma.cpp
		marnav/nmea/rmb.cpp
		marnav/nmea/rmc.cpp
		marnav/nmea/rot.cpp
		marnav/nmea/rpm.cpp
		marnav/nmea/rsa.cpp
		marnav/nmea/rsd.cpp
		marnav/nmea/rte.cpp
		marnav/nmea/sentence.cpp
		marnav/nmea/sfi.cpp
		marnav/nmea/split.cpp
		marnav/nmea/stalk.cpp
		marnav/nmea/stn.cpp
		marnav/nmea/string.cpp
		marnav/nmea/tag_block.cpp
		marnav/nmea/talker_id.cpp
		marnav/nmea/tds.cpp
		marnav/nmea/tfi.cpp
		marnav/nmea/time.cpp
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
		marnav/nmea/waypoint.cpp
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
		marnav/seatalk/seatalk.cpp
		marnav/utils/mmsi.cpp
		marnav/utils/mmsi_country.cpp
	)

include(CheckSymbolExists)
if(APPLE)
	check_symbol_exists(strtod_l xlocale.h HAVE_STRTOD_L)
else()
	check_symbol_exists(strtod_l stdlib.h HAVE_STRTOD_L)
endif()

if(DEFINED HAVE_STRTOD_L)
	target_sources(marnav PRIVATE marnav/nmea/io_double_strtodl.cpp)
else()
	target_sources(marnav PRIVATE marnav/nmea/io_double_strstream.cpp)
endif()

install(
	DIRECTORY
		${PROJECT_SOURCE_DIR}/include/marnav/ais
		${PROJECT_SOURCE_DIR}/include/marnav/geo
		${PROJECT_SOURCE_DIR}/include/marnav/math
		${PROJECT_SOURCE_DIR}/include/marnav/nmea
		${PROJECT_SOURCE_DIR}/include/marnav/seatalk
		${PROJECT_SOURCE_DIR}/include/marnav/units
		${PROJECT_SOURCE_DIR}/include/marnav/utils
	DESTINATION include/marnav
	)

if(ENABLE_IO)
	target_sources(marnav
		PRIVATE
			marnav/io/serial.cpp
			marnav/io/nmea_reader.cpp
			marnav/io/default_nmea_reader.cpp
			marnav/io/seatalk_reader.cpp
			marnav/io/default_seatalk_reader.cpp
		)
	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/include/marnav/io
		DESTINATION include/marnav
		)
endif()

target_include_directories(marnav
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
		$<INSTALL_INTERFACE:include>
	)

target_compile_options(marnav
	PRIVATE
		-pipe
		-ggdb
		-Wall
		-Wextra
		-pedantic-errors
		-Wold-style-cast
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
		-Wno-inline
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

if(CMAKE_BUILD_TYPE MATCHES Coverage)
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

# stuff for the config and config-version files
set(INCLUDE_INSTALL_DIR include)
set(LIB_INSTALL_DIR lib)
include(CMakePackageConfigHelpers)

set(targets_export_name ${PROJECT_NAME}-targets)

install(
	TARGETS marnav
	EXPORT ${targets_export_name}
	LIBRARY DESTINATION ${LIB_INSTALL_DIR}
	ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION ${INCLUDE_INSTALL_DIR}
	)

configure_package_config_file(
	config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	INSTALL_DESTINATION "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}"
	PATH_VARS INCLUDE_INSTALL_DIR
	)

install(
	EXPORT ${targets_export_name}
	NAMESPACE "${PROJECT_NAME}::"
	DESTINATION "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}"
	)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	VERSION "${PROJECT_VERSION}" COMPATIBILITY SameMajorVersion)

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	DESTINATION
		"${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}"
	)


if(ENABLE_TOOLS)
	### bin: nmeasum
	add_executable(nmeasum)
	target_sources(nmeasum PRIVATE nmeasum.cpp)
	target_link_libraries(nmeasum PRIVATE marnav::marnav)

	target_compile_options(nmeasum
		PRIVATE
			-pipe
			-ggdb
			-Wall
			-Wextra
			-pedantic-errors
		)

	### bin: nmeadump
	if(ENABLE_IO)
		add_executable(nmeadump)
		target_sources(nmeadump PRIVATE nmeadump.cpp)
		target_include_directories(nmeadump
			PRIVATE
				${CMAKE_CURRENT_SOURCE_DIR}
			)

		target_compile_options(nmeadump
			PRIVATE
				-pipe
				-ggdb
				-Wall
				-Wextra
				-pedantic-errors
			)

		target_link_libraries(nmeadump
			PRIVATE
				marnav::marnav
				cxxopts::cxxopts
				fmt::fmt
			)
	endif()
endif()
