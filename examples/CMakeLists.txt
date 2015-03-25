add_executable(parse_nmea
	parse_nmea.cpp
	)

target_link_libraries(parse_nmea
	marnav
	)
