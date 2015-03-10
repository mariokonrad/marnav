
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${CMAKE_CURRENT_BINARY_DIR}/../src
	)

add_executable(testrunner
	nmea/Test_mtw.cpp
	nmea/Test_rmc.cpp
	)

target_link_libraries(testrunner
	nmea
	gmock
	pthread
	)

run_unittest(testrunner)

