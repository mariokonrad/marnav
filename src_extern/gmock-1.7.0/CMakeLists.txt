cmake_minimum_required(VERSION 2.8.11)
project(gmock)
message(STATUS "TARGET: gmock 1.7.0")

if(UNIX)
	set(GMOCK_C_FLAGS   "-Wno-missing-field-initializers")
	set(GMOCK_CXX_FLAGS "-Wno-missing-field-initializers")
endif()

# gmock specific changes to the compiler flags
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} ${GMOCK_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${GMOCK_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${GMOCK_CXX_FLAGS}")

message("@@ ${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(gmock
	STATIC
	custom_main.cpp
	gmock-gtest-all.cc
	)

set_target_properties(gmock
	PROPERTIES VERSION 1.7.0
	SOVERSION 1.7.0
	)

install(
	TARGETS gmock
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	FILES gmock/gmock.h
	DESTINATION include/gmock
	)

install(
	FILES gtest/gtest.h
	DESTINATION include/gtest
	)

