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
