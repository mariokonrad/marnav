cmake_minimum_required(VERSION 3.0)
project(marnav)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "3")
set(VERSION_PATCH "7")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(ExternalProject)
include(ExternGmock)
include(GitInformation)

set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${GIT_COMMIT_HASH_SHORT}")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set(PROJECT_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
endif()

option(ENABLE_PROFILING "Enable Profiling" OFF)
option(ENABLE_WARNING_HELL "Enable Warning Hell" OFF)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	message(STATUS "Compiler settings for GNU")

	if(ENABLE_PROFILING)
		set(CXX_PROFILE_FLAGS "-pg")
	endif()

	set(GNU_CXX_WARNING_FLAGS "-Wall -Wextra -pedantic-errors")
	if(ENABLE_WARNING_HELL)
		message(STATUS "Behold: entering the hell of extended warnings")

		# some are not enabled on purpose
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Weffc++")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wcast-align")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wcast-qual")
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wconversion")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Werror")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wdisabled-optimization")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wfloat-equal")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wformat=2")
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wformat-nonliteral")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wformat-security")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wformat-y2k")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wimport")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Winit-self")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Winline")
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wlong-long")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wmissing-field-initializers")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wmissing-format-attribute")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wmissing-include-dirs")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wmissing-noreturn")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wold-style-cast")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Woverloaded-virtual")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wpacked")
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wpadded")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wpointer-arith")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wredundant-decls")
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wshadow")
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wstack-protector")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wstrict-aliasing=2")
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wswitch-enum")
		#set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wswitch-default")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wunreachable-code")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wunused")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wunused-parameter")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wvariadic-macros")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wwrite-strings")

		# explicitly disabled on purpose
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wno-unused-function")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wno-comment")
		set(GNU_CXX_WARNING_FLAGS "${GNU_CXX_WARNING_FLAGS} -Wno-format-nonliteral")
	endif()

	set(CMAKE_CXX_FLAGS          "${CMAKE_CXX_FLAGS}         ${CXX_PROFILE_FLAGS} -std=c++11 ${GNU_CXX_WARNING_FLAGS} -pipe -O0 -ggdb")
	set(CMAKE_CXX_FLAGS_DEBUG    "${CMAKE_CXX_FLAGS_DEBUG}   ${CXX_PROFILE_FLAGS} -std=c++11 ${GNU_CXX_WARNING_FLAGS} -pipe -O0 -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_PROFILE_FLAGS} -std=c++11 ${GNU_CXX_WARNING_FLAGS} -pipe -O3 -ggdb")
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

### common
file(MAKE_DIRECTORY
	${CMAKE_CURRENT_BINARY_DIR}/doc
	${CMAKE_CURRENT_BINARY_DIR}/doc/coverage
	${CMAKE_CURRENT_BINARY_DIR}/local/include
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
	message(STATUS "cppcheck found: ${CPPCHECK_PATH}")
	add_custom_target(cppcheck
		COMMAND ${CPPCHECK_PATH} --suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/cppcheck-suppress.txt --std=c++11 --platform=unix32 -v -f --enable=all --template='{file}:{line},{severity},{id},{message}' -I ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/test 2> ${CMAKE_CURRENT_BINARY_DIR}/doc/cppcheck.txt
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
