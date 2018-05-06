cmake_minimum_required(VERSION 3.2)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(GitInformation)

project(marnav VERSION 0.7.0 LANGUAGES CXX C)

### compiler check
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	message(STATUS "Compiler: GNU")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	message(STATUS "Compiler: Clang")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "Compiler: MSVC")
else()
	message(FATAL_ERROR "Unsupported compiler detected: ${CMAKE_CXX_COMPILER_ID}")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

git_commit_hash(GIT_COMMIT_HASH GIT_COMMIT_HASH_SHORT)
git_branch_name(GIT_BRANCH)

message(STATUS "git branch: ${GIT_BRANCH}")
message(STATUS "git commit hash: ${GIT_COMMIT_HASH}")

### version handling
if(NOT ("${CMAKE_BUILD_TYPE}" MATCHES "Release"))
	set(PROJECT_VERSION "${PROJECT_VERSION}-${GIT_COMMIT_HASH_SHORT}")
endif()
message(STATUS "Project Vesion: ${PROJECT_VERSION}")

### external projects
include(ExternalProject)

### options
option(ENABLE_PROFILING "Enable Profiling" OFF)
option(ENABLE_BENCHMARK "Enable Benchmark" OFF)
option(ENABLE_WARNING_HELL "Enable Warning Hell" OFF)
option(ENABLE_SANITIZER "Enable Sanitizing (address, undefined)" OFF)
option(ENABLE_AIS "Enable AIS support" ON)
option(ENABLE_SEATALK "Enable SeaTalk support" ON)
option(ENABLE_IO "Enable IO support" ON)
option(ENABLE_EXAMPLES "Enable Examples" ON)
option(ENABLE_TESTS "Enable Tests" ON)
option(ENABLE_TOOLS "Enable Tools" ON)

### common
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
file(MAKE_DIRECTORY
	${CMAKE_CURRENT_BINARY_DIR}/doc
	${CMAKE_CURRENT_BINARY_DIR}/doc/coverage
	${CMAKE_CURRENT_BINARY_DIR}/local/include
	)
string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type_lower)

### library
add_subdirectory(src)

### examples
message(STATUS "Build Examples: ${ENABLE_EXAMPLES}")
if(ENABLE_EXAMPLES)
	add_subdirectory(examples)
endif()

### ctags / cscope
include(CTags)
if(CTAGS_PATH AND CSCOPE_PATH)
	setup_ctags_target("${CMAKE_CURRENT_SOURCE_DIR}/src/*.?pp")
endif()

### documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
	git_authors(GIT_AUTHORS AUTHOR_LIST)
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
	message(STATUS "cppcheck found: ${CPPCHECK_PATH}")
	set(cppcheck_parameters --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/cppcheck-suppress.txt --std=c++11 -v -f --enable=all --template='{file}:{line},{severity},{id},{message}')
	if(UNIX)
		set(cppcheck_parameters ${cppcheck_parameters} --platform=unix32)
	elseif(WIN32)
		set(cppcheck_parameters ${cppcheck_parameters} --platform=win32W)
	endif()
	add_custom_target(cppcheck
		COMMAND ${CPPCHECK_PATH} ${cppcheck_parameters} -I ${CMAKE_CURRENT_SOURCE_DIR}/src -I ${CMAKE_CURRENT_BINARY_DIR}/local/include ${CMAKE_CURRENT_SOURCE_DIR}/src 2> ${CMAKE_CURRENT_BINARY_DIR}/doc/cppcheck.txt
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
else()
	message(STATUS "cppcheck not found, target not available.")
endif()

### testing common stuff
enable_testing()

### unit tests, assumes gtest (because of the program argument)
message(STATUS "Build Tests: ${ENABLE_TESTS}")
if(ENABLE_TESTS)
	include(ExternGmock)
	include(ExternBenchmark)
	add_custom_target(unittest)
	macro(run_unittest unittest_target)
		add_custom_target(${unittest_target}_runtest
			COMMAND ${unittest_target} --gtest_shuffle
			DEPENDS ${unittest_target}
			WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
			)
		add_dependencies(unittest ${unittest_target}_runtest)
	endmacro()

	add_subdirectory(test)
endif()

### coverage
if(build_type_lower MATCHES coverage)
	include(CodeCoverage)
	setup_target_for_coverage(coverage
		testrunner
		doc/coverage
		)
endif()


### package
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
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
