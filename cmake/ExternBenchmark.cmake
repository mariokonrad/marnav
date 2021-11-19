message(STATUS "Extern: benchmark 1.6.0")

set(benchmark_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/local")
set(benchmark_INCLUDE_DIR "${benchmark_INSTALL_DIR}/include")
set(benchmark_LIBRARY_DIR "${benchmark_INSTALL_DIR}/lib")

ExternalProject_Add(extern_benchmark
	PREFIX "${CMAKE_CURRENT_BINARY_DIR}/benchmark"
	SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/benchmark-1.6.0"
	# configure
	CMAKE_ARGS
		-DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
		-DCMAKE_INSTALL_PREFIX=${benchmark_INSTALL_DIR}
		-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
		-DBENCHMARK_ENABLE_TESTING=FALSE
		-DBENCHMARK_ENABLE_GTEST_TESTS=FALSE
	# install
	INSTALL_DIR ${benchmark_INSTALL_DIR}
	)

add_library(benchmark::benchmark STATIC IMPORTED)
set_target_properties(benchmark::benchmark
	PROPERTIES
		IMPORTED_LOCATION
			${benchmark_LIBRARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}benchmark${CMAKE_STATIC_LIBRARY_SUFFIX}
		INTERFACE_INCLUDE_DIRECTORIES
			${benchmark_INCLUDE_DIR}
	)
add_dependencies(benchmark::benchmark extern_benchmark)

