cmake_minimum_required(VERSION 3.19)

project(marnav
	VERSION 0.13.0
	LANGUAGES CXX C
	DESCRIPTION "Library for maritime navigation."
	)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# compilation traits
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

### options
option(ENABLE_STATIC "Enable static library" ON)
option(ENABLE_EXAMPLES "Enable Examples" ON)
option(ENABLE_TESTS "Enable Tests" ON)
option(ENABLE_TOOLS "Enable Tools" ON)

if(MSVC)
	set(CMAKE_DEBUG_POSTFIX "d")

	set(ENABLE_PROFILING OFF)
	set(ENABLE_BENCHMARK OFF)
	set(ENABLE_SANITIZER OFF)
	set(ENABLE_TESTS_BENCHMARK OFF)
	set(ENABLE_IWYU OFF)

	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
	set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin")
else()
	option(ENABLE_PROFILING "Enable Profiling" OFF)
	option(ENABLE_BENCHMARK "Enable Benchmark" OFF)
	option(ENABLE_SANITIZER "Enable Sanitizing (address, undefined)" OFF)
	option(ENABLE_TESTS_BENCHMARK "Enable Test Benchmarks" ON)
	option(ENABLE_IWYU "Enable include-what-you-use" OFF)
endif()

if(NOT DEFINED BUILD_SHARED_LIBS)
	if(ENABLE_STATIC)
		set(BUILD_SHARED_LIBS FALSE)
	else()
		set(BUILD_SHARED_LIBS TRUE)
	endif()
endif()

if(ENABLE_TESTS)
	set(BUILD_TESTING TRUE)
	enable_testing()
else()
	set(BUILD_TESTING FALSE)
endif()

# misc
include(RepoInformation)
include(Documentation)
include(CppCheck)
include(FetchContent)

if(ENABLE_TOOLS)
	set(CXXOPTS_BUILD_EXAMPLES FALSE CACHE BOOL "" FORCE)
	set(CXXOPTS_BUILD_TESTS FALSE CACHE BOOL "" FORCE)
	FetchContent_Declare(cxxopts
		URL "${CMAKE_CURRENT_SOURCE_DIR}/extern/cxxopts"
		)
	FetchContent_MakeAvailable(cxxopts)

	set(FMT_INSTALL TRUE CACHE BOOL "" FORCE)
	FetchContent_Declare(fmt
		URL "${CMAKE_CURRENT_SOURCE_DIR}/extern/fmt"
		)
	FetchContent_MakeAvailable(fmt)
endif()

### common
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
file(MAKE_DIRECTORY
	${CMAKE_CURRENT_BINARY_DIR}/doc
	${CMAKE_CURRENT_BINARY_DIR}/doc/coverage
	${CMAKE_CURRENT_BINARY_DIR}/local/include
	)

### library and tools
add_subdirectory(src)

### examples
message(STATUS "Build Examples       : ${ENABLE_EXAMPLES}")
if(ENABLE_EXAMPLES)
	add_subdirectory(examples)
endif()

### testing
message(STATUS "Build Tests          : ${ENABLE_TESTS}")
message(STATUS "Build Tests Benchmark: ${ENABLE_TESTS_BENCHMARK}")
if(ENABLE_TESTS)
	FetchContent_Declare(googletest
		URL "${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest-1.11.0"
		)
	FetchContent_MakeAvailable(googletest)

	if(ENABLE_TESTS_BENCHMARK)
		set(BENCHMARK_ENABLE_TESTING FALSE CACHE BOOL "" FORCE)
		set(BENCHMARK_ENABLE_GTEST_TESTS FALSE CACHE BOOL "" FORCE)
		FetchContent_Declare(benchmark
			URL "${CMAKE_CURRENT_SOURCE_DIR}/extern/benchmark-1.6.0"
			)
		FetchContent_MakeAvailable(benchmark)
	endif()

	add_subdirectory(test)
endif()

### coverage
if(CMAKE_BUILD_TYPE MATCHES Coverage)
	include(CodeCoverage)
	setup_target_for_coverage(coverage
		testrunner
		doc/coverage
		)
endif()

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
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
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libstdc++6 (>= 7.0)")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3)")
set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
if (CMAKE_SIZEOF_VOID_P MATCHES "8")
	set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
else()
	set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386")
endif()

include(CPack)
