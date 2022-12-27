add_executable(nmeasum)

target_sources(nmeasum
	PRIVATE
		nmeasum.cpp
	)

target_link_libraries(nmeasum PRIVATE marnav::marnav)

target_compile_features(nmeasum PRIVATE cxx_std_17)

target_compile_options(nmeasum
	PRIVATE
		-ggdb
		-Wall
		-Wextra
		-pedantic-errors
	)

