cmake_minimum_required(VERSION 3.0)
project(gmock VERSION 1.7.0 LANGUAGES CXX)
message(STATUS "TARGET: gmock 1.7.0")

if(UNIX)
	add_compile_options(
		-std=c++11
		-pipe
		-ggdb
		-Wall
		-Wextra
		-pedantic-errors
		# gmock specific changes to the compiler flags
		-Wno-missing-field-initializers
		)
endif()

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

