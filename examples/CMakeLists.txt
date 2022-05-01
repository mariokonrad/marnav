find_package(Boost 1.53.0 COMPONENTS system)

set_property(DIRECTORY PROPERTY COMPILE_OPTIONS
	-pipe
	-ggdb
	-Wall
	-Wextra
	-pedantic-errors
	)


add_executable(parse_nmea parse_nmea.cpp)
target_link_libraries(parse_nmea marnav::marnav)

add_executable(seatalk_snippets seatalk_snippets.cpp)
target_link_libraries(seatalk_snippets marnav::marnav)

add_executable(create_nmea_from_ais create_nmea_from_ais.cpp)
target_link_libraries(create_nmea_from_ais marnav::marnav)

add_executable(create_nmea_from_ais_2 create_nmea_from_ais_2.cpp)
target_link_libraries(create_nmea_from_ais_2 marnav::marnav)

add_executable(parse_ais parse_ais.cpp)
target_link_libraries(parse_ais marnav::marnav)

add_executable(select select.cpp)
target_link_libraries(select marnav::marnav)

add_executable(bitset_iterate bitset_iterate.cpp)
target_link_libraries(bitset_iterate marnav::marnav)

if(TARGET marnav::marnav-io)
	add_executable(read_seatalk read_seatalk.cpp)
	target_link_libraries(read_seatalk marnav::marnav marnav::marnav-io)

	add_executable(read_ais read_ais.cpp)
	target_link_libraries(read_ais marnav::marnav marnav::marnav-io)

	add_executable(nmea_multiplexer nmea_multiplexer.cpp)
	target_link_libraries(nmea_multiplexer marnav::marnav marnav::marnav-io)

	add_executable(read_nmea read_nmea.cpp)
	target_link_libraries(read_nmea marnav::marnav marnav::marnav-io)
endif()

if(Boost_FOUND AND (TARGET marnav::marnav-io))
	add_executable(read_nmea_boostasio read_nmea_boostasio.cpp)
	target_include_directories(read_nmea_boostasio PRIVATE ${Boost_INCLUDE_DIRS})
	target_link_libraries(read_nmea_boostasio
		marnav::marnav
		marnav::marnav-io
		${Boost_LIBRARIES}
		pthread
		)

	add_executable(seatalk_nmea_converter simple_seatalk_nmea_converter.cpp)
	target_include_directories(seatalk_nmea_converter PRIVATE ${Boost_INCLUDE_DIRS})
	target_link_libraries(seatalk_nmea_converter
		marnav::marnav
		marnav::marnav-io
		${Boost_LIBRARIES}
		pthread
		)

	add_executable(serial_to_tcp serial_to_tcp.cpp)
	target_include_directories(serial_to_tcp PRIVATE ${Boost_INCLUDE_DIRS})
	target_link_libraries(serial_to_tcp
		marnav::marnav
		marnav::marnav-io
		${Boost_LIBRARIES}
		pthread
		)
endif()

add_subdirectory(qtnmeadiag)
