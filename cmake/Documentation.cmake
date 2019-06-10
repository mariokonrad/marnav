find_package(Doxygen)
if(DOXYGEN_FOUND)
	if(GIT_REPO_FOUND)
		git_authors(GIT_AUTHORS AUTHOR_LIST)
	else()
		message(STATUS "no git repository found, using default authors list")
		set(AUTHOR_LIST "Mario Konrad, with help from others")
	endif()
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/doc/main.dox.in
		${CMAKE_CURRENT_BINARY_DIR}/doc/main.dox
		)
	configure_file(
		${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf.in
		${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
		)
	add_custom_target(doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
		)
	add_dependencies(doc tags)
endif()
