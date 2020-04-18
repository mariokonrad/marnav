message(STATUS "Extern: cxxopts 2.2.0")

set(cxxopts_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/local")
set(cxxopts_INCLUDE_DIR "${cxxopts_INSTALL_DIR}/include")
set(cxxopts_LIBRARY_DIR "${cxxopts_INSTALL_DIR}/lib")

ExternalProject_add(extern-cxxopts
	PREFIX "${CMAKE_CURRENT_BINARY_DIR}/cxxopts"
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/cxxopts"
	CMAKE_ARGS
		-DCMAKE_BUILD_TYPE=Release
		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
		-DCMAKE_INSTALL_PREFIX=${cxxopts_INSTALL_DIR}
		-DBUILD_SHARED_LIBS=FALSE
		-DCXXOPTS_BUILD_EXAMPLES=FALSE
		-DCXXOPTS_BUILD_TESTS=FALSE
	INSTALL_DIR ${cxxopts_INSTALL_DIR}
	)

add_library(cxxopts::cxxopts INTERFACE IMPORTED)
set_target_properties(cxxopts::cxxopts
	PROPERTIES
		INTERFACE_INCLUDE_DIRECTORIES
			${cxxopts_INCLUDE_DIR}
	)
add_dependencies(cxxopts::cxxopts extern-cxxopts)

