find_program(CPPCHECK_PATH cppcheck)
if(CPPCHECK_PATH)
	message(STATUS "cppcheck: ${CPPCHECK_PATH}")
	add_custom_target(cppcheck
		COMMAND ${CPPCHECK_PATH}
			--suppressions-list=${CMAKE_CURRENT_SOURCE_DIR}/src/cppcheck-suppress.txt
			--std=c++11
			--platform=unix32
			-v
			-f
			--enable=all
			--template='{file}:{line},{severity},{id},{message}'
			-I ${CMAKE_CURRENT_SOURCE_DIR}/src
			-I ${CMAKE_CURRENT_SOURCE_DIR}/include
			${CMAKE_CURRENT_SOURCE_DIR}/src
			${CMAKE_CURRENT_SOURCE_DIR}/include
			2> ${CMAKE_CURRENT_BINARY_DIR}/doc/cppcheck.txt
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)
else()
	message(STATUS "cppcheck: not found, target not available.")
endif()
