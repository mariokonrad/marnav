cmake_minimum_required(VERSION 3.11)
project(marnav-demo VERSION 0.0.0 LANGUAGES CXX C)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(LOCAL_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/local")

include(ExternalProject)
include(ExternMarnav)

add_subdirectory(src)
