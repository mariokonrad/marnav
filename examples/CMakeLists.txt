find_package(Boost 1.53.0
	COMPONENTS system
	)


add_executable(parse_nmea
	parse_nmea.cpp
	)

target_link_libraries(parse_nmea
	marnav
	)

add_executable(read_seatalk
	read_seatalk.cpp
	)

target_link_libraries(read_seatalk
	marnav
	)

add_executable(read_nmea
	read_nmea.cpp
	)

target_link_libraries(read_nmea
	marnav
	)

add_executable(read_ais
	read_ais.cpp
	)

target_link_libraries(read_ais
	marnav
	)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})

	add_executable(read_nmea_boostasio
		read_nmea_boostasio.cpp
		)

	target_link_libraries(read_nmea_boostasio
		marnav
		${Boost_LIBRARIES}
		)
endif()
