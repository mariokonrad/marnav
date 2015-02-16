cmake_minimum_required(VERSION 2.8)
project(nmea)

if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS         "-std=c++11 -Wall -Wextra -O0")
	set(CMAKE_CXX_FLAGS_DEBUG   "-std=c++11 -Wall -Wextra -O0")
	set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -Wextra -O3")
endif()


add_library(nmea
	src/nmea/angle.cpp
	src/nmea/date.cpp
	src/nmea/time.cpp
	src/nmea/sentence.cpp
	src/nmea/nmea.cpp
	src/nmea/mtw.cpp
	src/nmea/rmc.cpp
	src/nmea/optional.hpp
	src/nmea/unique.hpp
	)

set_target_properties(nmea
	PROPERTIES VERSION 0.0.1
	SOVERSION 0.0.1
	)

install(
	TARGETS nmea
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	FILES
		src/nmea/angle.hpp
		src/nmea/date.hpp
		src/nmea/time.hpp
		src/nmea/optional.hpp
		src/nmea/sentence.hpp
		src/nmea/unique.hpp
		src/nmea/nmea.hpp
		src/nmea/mtw.hpp
		src/nmea/rmc.hpp
	DESTINATION include/nmea
	)

include_directories(src)

add_executable(nmea_sentence
	nmea_sentence.cpp
	)

target_link_libraries(nmea_sentence
	nmea
	)

