cmake_minimum_required(VERSION 3.19)
project(foobar LANGUAGES CXX VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(foobar foobar.cpp)
target_link_libraries(foobar marnav::marnav)

set(ENABLE_EXAMPLES OFF CACHE BOOL "")
set(ENABLE_TESTS    OFF CACHE BOOL "")
set(ENABLE_TOOLS    OFF CACHE BOOL "")
add_subdirectory(${MARNAV_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/marnav)
