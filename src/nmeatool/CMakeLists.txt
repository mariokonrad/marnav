add_executable(nmeatool)

target_sources(nmeatool
	PRIVATE
		nmeatool.cpp
	)

target_compile_features(nmeatool PRIVATE cxx_std_17)

target_compile_options(nmeatool
	PRIVATE
		-ggdb
		-Wall
		-Wextra
		-pedantic-errors
	)

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

