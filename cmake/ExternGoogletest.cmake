message(STATUS "Extern: googletest 1.11.0")

set(googletest_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/local")
set(googletest_INCLUDE_DIR "${googletest_INSTALL_DIR}/include")
set(googletest_LIBRARY_DIR "${googletest_INSTALL_DIR}/lib")

ExternalProject_Add(extern-googletest
	PREFIX "${CMAKE_CURRENT_BINARY_DIR}/googletest"
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/googletest-1.11.0"
	# configure
	CMAKE_ARGS
		-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
		-DCMAKE_INSTALL_PREFIX=${googletest_INSTALL_DIR}

		# Build always release, I don't see a point debugging googletest.
		# Also, the postfix 'd' for output names in debug builds is hardcoded,
		# in googletest. WTF!?
		-DCMAKE_BUILD_TYPE=Release
	# install
	INSTALL_DIR ${googletest_INSTALL_DIR}
	BUILD_BYPRODUCTS
		${googletest_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
		${googletest_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
		${googletest_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}
		${googletest_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX}
	)

add_library(googletest::gtest STATIC IMPORTED)
set_target_properties(googletest::gtest
	PROPERTIES
		IMPORTED_LOCATION
			${googletest_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
		INTERFACE_INCLUDE_DIRECTORIES
			${googletest_INCLUDE_DIR}
	)
add_dependencies(googletest::gtest extern-googletest)

add_library(googletest::gtest_main STATIC IMPORTED)
set_target_properties(googletest::gtest_main
	PROPERTIES
		IMPORTED_LOCATION
			${googletest_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
add_dependencies(googletest::gtest_main extern-googletest)

add_library(googletest::gmock STATIC IMPORTED)
set_target_properties(googletest::gmock
	PROPERTIES
		IMPORTED_LOCATION
			${googletest_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock${CMAKE_STATIC_LIBRARY_SUFFIX}
		INTERFACE_INCLUDE_DIRECTORIES
			${googletest_INCLUDE_DIR}
	)
add_dependencies(googletest::gmock extern-googletest)

add_library(googletest::gmock_main STATIC IMPORTED)
set_target_properties(googletest::gmock_main
	PROPERTIES
		IMPORTED_LOCATION
			${googletest_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}gmock_main${CMAKE_STATIC_LIBRARY_SUFFIX}
	)
add_dependencies(googletest::gmock_main extern-googletest)

