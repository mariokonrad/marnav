message(STATUS "Extern: cxxopts pre 1.0.0")

find_path(cxxopts_INCLUDE_DIR
	cxxopts/cxxopts.hpp
	PATHS ${CMAKE_CURRENT_SOURCE_DIR}/extern
)

if(cxxopts_INCLUDE_DIR)
	add_library(cxxopts::cxxopts INTERFACE IMPORTED)
	set_target_properties(cxxopts::cxxopts
		PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES ${cxxopts_INCLUDE_DIR}
		)
endif()

