cmake_minimum_required(VERSION 2.8)
project(nmea)

if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS         "-std=c++11 -Wall -Wextra -O0")
	set(CMAKE_CXX_FLAGS_DEBUG   "-std=c++11 -Wall -Wextra -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -Wextra -O3")
endif()


add_library(nmea
	angle.cpp
	date.cpp
	time.cpp
	sentence.cpp
	nmea.cpp
	mtw.cpp
	rmc.cpp
	optional.hpp
	unique.hpp
	)

set_target_properties(nmea
	PROPERTIES VERSION 0.0.1
	SOVERSION 0.0.1
	)

add_executable(nmea_sentence
	nmea_sentence.cpp
	)

target_link_libraries(nmea_sentence
	nmea
	)

