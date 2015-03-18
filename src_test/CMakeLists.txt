
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${CMAKE_CURRENT_BINARY_DIR}/../src
	)

add_executable(testrunner
	nmea/Test_aam.cpp
	nmea/Test_hdg.cpp
	nmea/Test_mtw.cpp
	nmea/Test_mwv.cpp
	nmea/Test_rmc.cpp
	nmea/Test_vhw.cpp
	nmea/Test_vlw.cpp
	nmea/Test_vwr.cpp
	nmea/Test_vdm.cpp
	nmea/Test_vdo.cpp
	ais/Test_ais.cpp
	ais/Test_message_01.cpp
	ais/Test_message_02.cpp
	ais/Test_message_03.cpp
	)

target_link_libraries(testrunner
	nmea
	ais
	gmock
	pthread
	)

run_unittest(testrunner)

