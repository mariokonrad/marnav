cmake_minimum_required(VERSION 3.19)
project(foobar LANGUAGES CXX VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(marnav REQUIRED)

add_executable(foobar foobar.cpp)
target_link_libraries(foobar PRIVATE marnav::marnav)

if(TARGET marnav::marnav-io)
	target_compile_definitions(foobar PRIVATE HAVE_IO)
	target_link_libraries(foobar PRIVATE marnav::marnav-io)
endif()
