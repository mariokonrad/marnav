
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${CMAKE_CURRENT_BINARY_DIR}/../src
	)

add_executable(testrunner
	nmea/Test_nmea_sentence.cpp
	nmea/Test_nmea_aam.cpp
	nmea/Test_nmea_hdg.cpp
	nmea/Test_nmea_mtw.cpp
	nmea/Test_nmea_mwv.cpp
	nmea/Test_nmea_rmc.cpp
	nmea/Test_nmea_vhw.cpp
	nmea/Test_nmea_vlw.cpp
	nmea/Test_nmea_vwr.cpp
	nmea/Test_nmea_vdm.cpp
	nmea/Test_nmea_vdo.cpp
	ais/Test_ais.cpp
	ais/Test_ais_message_01.cpp
	ais/Test_ais_message_02.cpp
	ais/Test_ais_message_03.cpp
	ais/Test_ais_message_05.cpp
	)

target_link_libraries(testrunner
	marnav
	gmock
	pthread
	)

run_unittest(testrunner)

