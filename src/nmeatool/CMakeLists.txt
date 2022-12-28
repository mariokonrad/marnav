add_executable(nmeatool)

if(MSVC)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/resource.rc.in
		${CMAKE_CURRENT_BINARY_DIR}/resource.rc
		@ONLY
		)
endif()

target_sources(nmeatool
	PRIVATE
		$<$<AND:$<CXX_COMPILER_ID:MSVC>,$<BOOL:${BUILD_SHARED_LIBS}>>:${CMAKE_CURRENT_BINARY_DIR}/resource.rc>
		nmeatool.cpp
	)

target_compile_features(nmeatool PRIVATE cxx_std_17)

if(MSVC)
	# TODO
else()
	target_compile_options(nmeatool
		PRIVATE
			-ggdb
			-Wall
			-Wextra
			-pedantic-errors
		)
endif()

target_compile_definitions(nmeatool
	PRIVATE
		$<$<BOOL:${support_for_io}>:HAVE_IO>
	)

target_link_libraries(nmeatool
	PRIVATE
		marnav::marnav
		$<$<BOOL:${support_for_io}>:marnav::marnav-io>
		cxxopts
		fmt::fmt
	)

if(ENABLE_TESTS)
	add_test(NAME nmeatool-completeness
		COMMAND $<TARGET_FILE:nmeatool> --help-nmea-list
		)

	set_tests_properties(nmeatool-completeness
		PROPERTIES
			FAIL_REGULAR_EXPRESSION "\\* [A-Z]+"
		)
endif()

