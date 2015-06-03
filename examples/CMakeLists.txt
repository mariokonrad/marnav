find_package(Boost 1.53.0
	COMPONENTS system
	)

add_executable(parse_nmea parse_nmea.cpp)
target_link_libraries(parse_nmea marnav)

add_executable(read_seatalk read_seatalk.cpp)
target_link_libraries(read_seatalk marnav)

add_executable(read_nmea read_nmea.cpp)
target_link_libraries(read_nmea marnav)

add_executable(read_ais read_ais.cpp)
target_link_libraries(read_ais marnav)

add_executable(nmea_multiplexer nmea_multiplexer.cpp)
target_link_libraries(nmea_multiplexer marnav)

add_executable(bitset_iterate bitset_iterate.cpp)

add_executable(create_nmea_from_ais create_nmea_from_ais.cpp)
target_link_libraries(create_nmea_from_ais marnav)

add_executable(select select.cpp)
target_link_libraries(select marnav)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})

	add_executable(read_nmea_boostasio
		read_nmea_boostasio.cpp
		)
	target_link_libraries(read_nmea_boostasio
		marnav
		${Boost_LIBRARIES}
		)

	add_executable(seatalk_nmea_converter
		simple_seatalk_nmea_converter.cpp
		)
	target_link_libraries(seatalk_nmea_converter
		marnav
		${Boost_LIBRARIES}
		)
endif()

add_subdirectory(qtnmeadiag)
