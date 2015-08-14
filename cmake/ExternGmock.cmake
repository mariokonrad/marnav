message(STATUS "Extern: gmock 1.7.0")

set(gmock_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/local")
set(gmock_INCLUDE_DIR "${gmock_INSTALL_DIR}/include")
set(gmock_LIBRARY_DIR "${gmock_INSTALL_DIR}/lib")

ExternalProject_Add(extern_gmock
	PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gmock"
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/gmock-1.7.0"
	# configure
	CMAKE_ARGS
		-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
		-DCMAKE_INSTALL_PREFIX=${gmock_INSTALL_DIR}
		-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
	# install
	INSTALL_DIR ${gmock_INSTALL_DIR}
	)

add_library(gmock STATIC IMPORTED)
set_target_properties(gmock
	PROPERTIES
		IMPORTED_LOCATION
			${gmock_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
add_dependencies(gmock extern_gmock)
include_directories(${gmock_INCLUDE_DIR})

