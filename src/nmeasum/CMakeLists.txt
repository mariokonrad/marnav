add_executable(nmeasum)

if(MSVC)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/resource.rc.in
		${CMAKE_CURRENT_BINARY_DIR}/resource.rc
		@ONLY
		)
endif()

target_sources(nmeasum
	PRIVATE
		$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUILD_SHARED_LIBS}>>:${CMAKE_CURRENT_BINARY_DIR}/resource.rc>
		nmeasum.cpp
	)

target_link_libraries(nmeasum PRIVATE marnav::marnav)

target_compile_features(nmeasum PRIVATE cxx_std_17)

if(MSVC)
	# TODO
else()
	target_compile_options(nmeasum
		PRIVATE
			-ggdb
			-Wall
			-Wextra
			-pedantic-errors
		)
endif()

