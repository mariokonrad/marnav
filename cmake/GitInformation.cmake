find_package(Git)
set(GIT_BRANCH "<unknown>")
set(GIT_COMMIT_HASH "<unknown>")
if (GIT_FOUND)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} log -1 --format=format:%H HEAD
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		OUTPUT_VARIABLE GIT_COMMIT_HASH
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	message(STATUS "git branch: ${GIT_BRANCH}")
	message(STATUS "git commit hash: ${GIT_COMMIT_HASH}")
endif()
