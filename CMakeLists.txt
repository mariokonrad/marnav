cmake_minimum_required(VERSION 3.0)
project(marnav)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "3")
set(VERSION_PATCH "5")
set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

option(ENABLE_PROFILING "Enable Profiling" OFF)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	message(STATUS "Compiler settings for GNU")

	if(ENABLE_PROFILING)
		set(CXX_PROFILE_FLAGS "-pg")
	endif()

	set(CMAKE_CXX_FLAGS          "${CMAKE_CXX_FLAGS}         ${CXX_PROFILE_FLAGS} -std=c++11 -Wall -Wextra -pedantic-errors -pipe -O0 -ggdb")
	set(CMAKE_CXX_FLAGS_DEBUG    "${CMAKE_CXX_FLAGS_DEBUG}   ${CXX_PROFILE_FLAGS} -std=c++11 -Wall -Wextra -pedantic-errors -pipe -O0 -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_PROFILE_FLAGS} -std=c++11 -Wall -Wextra -pedantic-errors -pipe -O3 -ggdb")
	set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG}   ${CXX_PROFILE_FLAGS} --coverage -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	message(STATUS "Compiler settings for Clang")
	set(CMAKE_CXX_FLAGS          "${CMAKE_CXX_FLAGS}         -std=c++11 -Wall -Wextra -O0 -g")
	set(CMAKE_CXX_FLAGS_DEBUG    "${CMAKE_CXX_FLAGS_DEBUG}   -std=c++11 -Wall -Wextra -O0 -g")
	set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wall -Wextra -O4 -g")
	set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG}   --coverage -fprofile-arcs -ftest-coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
else()
	message(STATUS "Compiler settings for <unknown>")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(ExternalProject)
include(ExternGmock)
include(GitInformation)

### common
file(MAKE_DIRECTORY
	${CMAKE_CURRENT_BINARY_DIR}/doc
	${CMAKE_CURRENT_BINARY_DIR}/doc/coverage
	)

### library
include_directories(src)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)
add_subdirectory(src)

### examples
add_subdirectory(examples)

### ctags / cscope
find_program(CTAGS_PATH ctags)
find_program(CSCOPE_PATH cscope)
if(CTAGS_PATH AND CSCOPE_PATH)
	message(STATUS "Found ctags: ${CTAGS_PATH}")
	message(STATUS "Found cscope: ${CSCOPE_PATH}")

	set_source_files_properties(cscope.files PROPERTIES GENERATED true)
	set_source_files_properties(cscope.out PROPERTIES GENERATED true)
	set_source_files_properties(tags PROPERTIES GENERATED true)

	file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.?pp")
	string(REPLACE ";" "\n" SOURCE_FILES "${SOURCE_FILES}")
	file(WRITE "${CMAKE_BINARY_DIR}/cscope.files.in" "${SOURCE_FILES}")
	configure_file("${CMAKE_BINARY_DIR}/cscope.files.in" "${CMAKE_BINARY_DIR}/cscope.files" COPYONLY)

	add_custom_target(tags
		COMMAND ${CTAGS_PATH} --c++-kinds=+p --fields=+iaS --extra=+q -L ${CMAKE_BINARY_DIR}/cscope.files
		COMMAND ${CSCOPE_PATH} -b
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		)
endif()

### documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/doc/main.dox.in
		${CMAKE_CURRENT_BINARY_DIR}/doc/main.dox
		)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in
		${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
		)
	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
		)
	add_dependencies(doc tags)
endif()

### cppcheck
find_program(CPPCHECK_PATH cppcheck)
if(CPPCHECK_PATH)
	message(STATUS "cppcheck found")
	add_custom_target(cppcheck
		COMMAND ${CPPCHECK_PATH} --std=c++11 --platform=unix32 -v -f --enable=all -I ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test 2> ${CMAKE_CURRENT_BINARY_DIR}/doc/cppcheck.txt
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
else()
	message(STATUS "cppcheck not found, target not available.")
endif()

### testing common stuff
enable_testing()

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

add_subdirectory(test)

### coverage
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
	include(CodeCoverage)
	setup_target_for_coverage(coverage
		testrunner
		doc/coverage
		)
endif()


### package
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CPACK_PACKAGE_NAME "marnav")
set(CPACK_PACKAGE_VENDOR "Mario Konrad")
set(CPACK_PACKAGE_CONTACT "Mario Konrad <mario.konrad@gmx.net>")
set(CPACK_PACAKGE_DESCRIPTION "Library for maritime navigation.")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Library")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_MONOLITHIC_INSTALL 1)
#set(CPACK_PACKAGE_EXECUTABLES "??" "??")
set(CPACK_STRIP_FILES true)

# package: debian
set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_DEBIAN_PACKAGE_NAME})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER ${CPACK_PACKAGE_CONTACT})
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${CPACK_PACAKGE_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libstdc++6 (>= 4.8)")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3)")
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
if (CMAKE_SIZEOF_VOID_P MATCHES "8")
	set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
else()
	set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386")
endif()

include(CPack)
