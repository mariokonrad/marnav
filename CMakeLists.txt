cmake_minimum_required(VERSION 3.11)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(marnav
	VERSION 0.9.0
	LANGUAGES CXX C
	DESCRIPTION "Library for maritime navigation."
	)

### compiler check
if(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU|Clang")
	message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
else()
	message(FATAL_ERROR "Unsupported compiler detected: ${CMAKE_CXX_COMPILER_ID}")
endif()

# compilation traits
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

### options
option(ENABLE_STATIC "Enable static library" ON)
option(ENABLE_PROFILING "Enable Profiling" OFF)
option(ENABLE_BENCHMARK "Enable Benchmark" OFF)
option(ENABLE_SANITIZER "Enable Sanitizing (address, undefined)" OFF)
option(ENABLE_IO "Enable IO support" ON)
option(ENABLE_EXAMPLES "Enable Examples" ON)
option(ENABLE_TESTS "Enable Tests" ON)
option(ENABLE_TOOLS "Enable Tools" ON)

if(${ENABLE_STATIC})
	set(BUILD_SHARED_LIBS FALSE)
else()
	set(BUILD_SHARED_LIBS TRUE)
endif()

# misc
include(RepoInformation)
include(Documentation)
include(CppCheck)
include(ExternalProject)

if(ENABLE_TOOLS)
	include(ExternCxxopts)
	include(ExternFmt)
endif()

### common
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
file(MAKE_DIRECTORY
	${CMAKE_CURRENT_BINARY_DIR}/doc
	${CMAKE_CURRENT_BINARY_DIR}/doc/coverage
	${CMAKE_CURRENT_BINARY_DIR}/local/include
	)

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
	setup_ctags_target("${CMAKE_CURRENT_SOURCE_DIR}/src/*.?pp;${CMAKE_CURRENT_SOURCE_DIR}/include/*.?pp")
endif()

### testing
message(STATUS "Build Tests: ${ENABLE_TESTS}")
if(ENABLE_TESTS)
	enable_testing()
	include(ExternGmock)
	include(ExternBenchmark)
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

include(Packaging)
