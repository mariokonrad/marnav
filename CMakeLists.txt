cmake_minimum_required(VERSION 2.8)
project(nmea)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATH  "0")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(ExternalProject)
include(ExternGmock)
include(GitInformation)

if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}         -std=c++11 -Wall -Wextra -O0 -ggdb")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -std=c++11 -Wall -Wextra -O0 -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wall -Wextra -O3 -ggdb")
endif()

### library
include_directories(src)
add_subdirectory(src)

### documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in
		${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
		)
	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
		)
endif()

### unit tests
add_custom_target(unittest)
macro(run_unittest unittest_target)
	add_custom_target(${unittest_target}_runtest
		COMMAND ${unittest_target}
		DEPENDS ${unittest_target}
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
		)
	add_dependencies(unittest ${unittest_target}_runtest)
endmacro()

add_subdirectory(src_test)

