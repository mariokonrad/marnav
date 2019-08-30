find_package(Git)
if (GIT_FOUND)

	# checks the current source directory for the presence of
	# a git repository.
	#
	# usage:
	#
	#    git_check_repository(GIT_REPO_FOUND)
	#
	function(git_check_repository found)
		if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.git)
			set(${found} TRUE  PARENT_SCOPE)
		else()
			set(${found} FALSE PARENT_SCOPE)
		endif()
	endfunction()

	# get commit hash of HEAD
	#
	# This function assumes to have a git repository present.
	#
	# usage:
	#
	#    git_commit_hash(GIT_HASH)
	#
	# an optional second argument is supported, which returns
	# the short version of the hash:
	#
	#    git_commit_hash(GIT_HASH GIT_HASH_SHORT)
	#
	function(git_commit_hash hash)
		if(${ARGC} GREATER 2)
			message(FATAL "too many arugments for `git_commit_hash`")
			return()
		endif()

		execute_process(
			COMMAND ${GIT_EXECUTABLE} log -1 --format=format:%H HEAD
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE commit_hash
			OUTPUT_STRIP_TRAILING_WHITESPACE
			)
		set(${hash} ${commit_hash} PARENT_SCOPE)

		if(${ARGC} GREATER 1)
			string(SUBSTRING "${commit_hash}" 0 7 commit_hash_short)
			set(${ARGV1} ${commit_hash_short} PARENT_SCOPE)
		endif()
	endfunction()

	# get branch name
	#
	# This function assumes to have a git repository present.
	#
	# usage:
	#
	#    git_branch_name(GIT_BRANCH)
	#
	function(git_branch_name branch_name)
		execute_process(
			COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE branch
			OUTPUT_STRIP_TRAILING_WHITESPACE
			)
		set(${branch_name} ${branch} PARENT_SCOPE)
	endfunction()

	# generate list of authors
	#
	# This function assumes to have a git repository present.
	#
	# usage:
	#
	#    git_authtors(GIT_AUTHOS)
	#
	# function is able to return a nice bullet point list also.
	# pass a second argument to the function:
	#
	#    git_authors(AUTHORS AUTHORS_LIST)
	#
	function(git_authors authors)
		if(${ARGC} GREATER 2)
			message(FATAL "too many arugments for `git_authors`")
		endif()

		execute_process(
			COMMAND ${GIT_EXECUTABLE} log --format=%an
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE GIT_AUTHORS
			OUTPUT_STRIP_TRAILING_WHITESPACE
			)
		string(REPLACE "\n" ";" GIT_AUTHORS "${GIT_AUTHORS}")
		list(SORT GIT_AUTHORS)
		list(REMOVE_DUPLICATES GIT_AUTHORS)
		set(${authors} ${GIT_AUTHORS} PARENT_SCOPE)

		if(${ARGC} GREATER 1)
			set(GIT_AUTHORS_LIST "")
			foreach(AUTHOR ${GIT_AUTHORS})
				string(CONCAT GIT_AUTHORS_LIST ${GIT_AUTHORS_LIST} "- ${AUTHOR}\n")
			endforeach(AUTHOR)
			set(${ARGV1} ${GIT_AUTHORS_LIST} PARENT_SCOPE)
		endif()
	endfunction()

	# returns the tag that points at HEAD, empty if none
	#
	# usage:
	#
	#    git_head_tag(TAG)
	#
	function(git_head_tag tag)
		execute_process(
			COMMAND ${GIT_EXECUTABLE} tag --points-at HEAD
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
			OUTPUT_VARIABLE head_tag
			OUTPUT_STRIP_TRAILING_WHITESPACE
			)
		set(${tag} ${head_tag} PARENT_SCOPE)
	endfunction()
endif()
