cmake_minimum_required(VERSION 2.8)
project(nmea)

if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}         -std=c++11 -Wall -Wextra -O0 -ggdb")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -std=c++11 -Wall -Wextra -O0 -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wall -Wextra -O3 -ggdb")
endif()

add_subdirectory(src)

include_directories(src)

add_executable(nmea_sentence
	nmea_sentence.cpp
	)

target_link_libraries(nmea_sentence
	nmea
	)

