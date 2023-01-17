cmake_minimum_required(VERSION 3.19)

include(GNUInstallDirs)

if(UNIX)
	set(CMAKE_SKIP_BUILD_RPATH FALSE)
	set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}:$ORIGIN/../${CMAKE_INSTALL_LIBDIR}:$$ORIGIN/../${CMAKE_INSTALL_LIBDIR}:$ORIGIN/..:$$ORIGIN/..")
	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

file(WRITE ${CMAKE_BINARY_DIR}/io-test.cpp [[
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
int main() {}
]])
try_compile(support_for_io ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/io-test.cpp)

### lib: marnav

message(STATUS "Target System        : ${CMAKE_SYSTEM_NAME}")
message(STATUS "Target Architecture  : ${CMAKE_SYSTEM_PROCESSOR}")

message(STATUS "Build shared library : ${BUILD_SHARED_LIBS}")
message(STATUS "Build Tools          : ${ENABLE_TOOLS}")
message(STATUS "Build IO support     : ${support_for_io}")
message(STATUS "Build for Profiliing : ${ENABLE_PROFILING}")
message(STATUS "Build for Benchmark  : ${ENABLE_BENCHMARK}")

if(MSVC)
	# TODO
else()
	set(common_compile_options
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
		-Wfloat-conversion
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
endif()

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/marnav/version.cpp.in
	${CMAKE_CURRENT_BINARY_DIR}/src/marnav/version.cpp
	@ONLY
	)

if(MSVC)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/marnav/resource.rc.in
		${CMAKE_CURRENT_BINARY_DIR}/src/marnav/resource.rc
		@ONLY
		)
endif()

add_library(marnav)
add_library(marnav::marnav ALIAS marnav)

target_compile_features(marnav
	PRIVATE
		cxx_std_17
	)

target_sources(marnav
	PRIVATE
		$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUILD_SHARED_LIBS}>>:${CMAKE_CURRENT_BINARY_DIR}/src/marnav/resource.rc>
		${CMAKE_CURRENT_BINARY_DIR}/src/marnav/version.cpp
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
		marnav/nmea/ack.cpp
		marnav/nmea/ais_helper.cpp
		marnav/nmea/alm.cpp
		marnav/nmea/alr.cpp
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
		marnav/nmea/mta.cpp
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
		marnav/nmea/route.cpp
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
		marnav/nmea/tep.cpp
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
		marnav/nmea/version.cpp
		marnav/nmea/vhw.cpp
		marnav/nmea/vlw.cpp
		marnav/nmea/vpw.cpp
		marnav/nmea/vtg.cpp
		marnav/nmea/vwe.cpp
		marnav/nmea/vwr.cpp
		marnav/nmea/waypoint.cpp
		marnav/nmea/wcv.cpp
		marnav/nmea/wdc.cpp
		marnav/nmea/wdr.cpp
		marnav/nmea/wnc.cpp
		marnav/nmea/wpl.cpp
		marnav/nmea/xdr.cpp
		marnav/nmea/xte.cpp
		marnav/nmea/xtr.cpp
		marnav/nmea/zda.cpp
		marnav/nmea/zdl.cpp
		marnav/nmea/zfi.cpp
		marnav/nmea/zfo.cpp
		marnav/nmea/zlz.cpp
		marnav/nmea/zpi.cpp
		marnav/nmea/zta.cpp
		marnav/nmea/zte.cpp
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

target_include_directories(marnav
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	)

target_compile_options(marnav
	PRIVATE
		${common_compile_options}
		$<$<BOOL:${ENABLE_PROFILING}>:-pg>
		$<$<BOOL:${ENABLE_BENCHMARK}>:-fno-omit-frame-pointer>
	)

include(CheckSymbolExists)
if(APPLE)
	check_symbol_exists(strtod_l xlocale.h HAVE_STRTOD_L)
else()
	check_symbol_exists(strtod_l stdlib.h HAVE_STRTOD_L)
endif()

if(DEFINED HAVE_STRTOD_L AND NOT MSVC)
	target_sources(marnav PRIVATE marnav/nmea/io_double_strtodl.cpp)
else()
	target_sources(marnav PRIVATE marnav/nmea/io_double_strstream.cpp)
endif()

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/include/marnav
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
	)

set_target_properties(marnav
	PROPERTIES
		VERSION "${PROJECT_VERSION}"
		SOVERSION "${PROJECT_VERSION}"
		WINDOWS_EXPORT_ALL_SYMBOLS TRUE
	)

if(support_for_io)
	add_library(marnav-io)
	add_library(marnav::marnav-io ALIAS marnav-io)

	target_compile_features(marnav-io
		PRIVATE
			cxx_std_17
		)

	target_sources(marnav-io
		PRIVATE
			marnav-io/serial.cpp
			marnav-io/nmea_reader.cpp
			marnav-io/default_nmea_reader.cpp
			marnav-io/seatalk_reader.cpp
			marnav-io/default_seatalk_reader.cpp
		)

	target_compile_options(marnav-io
		PRIVATE
			${common_compile_options}
		)

	target_include_directories(marnav-io
		PRIVATE
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		PUBLIC
			$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
		)

	target_link_libraries(marnav-io
		PUBLIC
			marnav::marnav
		)

	set_target_properties(marnav-io
		PROPERTIES
			VERSION "${PROJECT_VERSION}"
			SOVERSION "${PROJECT_VERSION}"
		)

	install(
		DIRECTORY ${PROJECT_SOURCE_DIR}/include/marnav-io
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/
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

if(ENABLE_IWYU)
	find_program(iwyu_bin NAMES iwyu include-what-you-use REQUIRED)
	if(iwyu_bin)
		message(STATUS "Found iwyu: ${iwyu_bin}")
		set(iwyu_args
			${iwyu_bin}
			-Xiwyu
			--no_comments
			-I${PROJECT_SOURCE_DIR}/include
			)
		set_property(TARGET marnav
			PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_args})
	endif()
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

# stuff for the config and config-version files
set(include_install_dir ${CMAKE_INSTALL_INCLUDEDIR})
include(CMakePackageConfigHelpers)

set(targets_export_name ${PROJECT_NAME}-targets)

install(
	TARGETS marnav
	EXPORT ${targets_export_name}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	INCLUDES DESTINATION ${include_install_dir}
	)

if(TARGET marnav-io)
	install(
		TARGETS marnav-io
		EXPORT ${targets_export_name}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		INCLUDES DESTINATION ${include_install_dir}
		)
endif()

configure_package_config_file(
	config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
	PATH_VARS include_install_dir
	)

install(
	EXPORT ${targets_export_name}
	NAMESPACE "${PROJECT_NAME}::"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
	)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	VERSION "${PROJECT_VERSION}" COMPATIBILITY SameMajorVersion)

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	DESTINATION
		"${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
	)

if(ENABLE_TOOLS)
	add_subdirectory(nmeatool)
	add_subdirectory(nmeasum)

	install(
		TARGETS nmeatool nmeasum
		EXPORT ${targets_export_name}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
		INCLUDES DESTINATION ${include_install_dir}
		)
endif()
