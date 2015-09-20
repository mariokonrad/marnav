find_package(Git)
set(GIT_BRANCH "<unknown>")
set(GIT_COMMIT_HASH "<unknown>")
if (GIT_FOUND)

	# get commit hash of HEAD
	execute_process(
		COMMAND ${GIT_EXECUTABLE} log -1 --format=format:%H HEAD
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		OUTPUT_VARIABLE GIT_COMMIT_HASH
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	string(SUBSTRING "${GIT_COMMIT_HASH}" 0 7 GIT_COMMIT_HASH_SHORT)

	# get branch name
	execute_process(
		COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)

	# generate list of authors
	execute_process(
		COMMAND ${GIT_EXECUTABLE} log --format=%an
		WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
		OUTPUT_VARIABLE GIT_AUTHORS
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	string(REPLACE "\n" ";" GIT_AUTHORS "${GIT_AUTHORS}")
	list(SORT GIT_AUTHORS)
	list(REMOVE_DUPLICATES GIT_AUTHORS)
	set(AUTHORS_LIST "")
	foreach(AUTHOR ${GIT_AUTHORS})
		string(CONCAT AUTHORS_LIST ${AUTHORS_LIST} "- ${AUTHOR}\n")
	endforeach(AUTHOR)

	message(STATUS "git branch: ${GIT_BRANCH}")
	message(STATUS "git commit hash: ${GIT_COMMIT_HASH}")
	message(STATUS "git authors: ${GIT_AUTHORS}")
endif()
