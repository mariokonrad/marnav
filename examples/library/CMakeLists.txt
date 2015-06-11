cmake_minimum_required(VERSION 3.0)
project(foobar)

find_package(marnav REQUIRED)

include_directories("${marnav_INCLUDE_DIR}")
add_executable(foobar foobar.cpp)
target_link_libraries(foobar ${marnav_LIBRARIES})

set_property(TARGET foobar PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET foobar PROPERTY CXX_STANDARD 11)

