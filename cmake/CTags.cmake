# Copyright (c) 2016 Mario Konrad
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its contributors
#    may be used to endorse or promote products derived from this software without
#    specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

find_program(CTAGS_PATH ctags)
find_program(CSCOPE_PATH cscope)

if(CTAGS_PATH AND CSCOPE_PATH)
	message(STATUS "Found ctags: ${CTAGS_PATH}")
	message(STATUS "Found cscope: ${CSCOPE_PATH}")

	set_source_files_properties(cscope.files PROPERTIES GENERATED true)
	set_source_files_properties(cscope.out PROPERTIES GENERATED true)
	set_source_files_properties(tags PROPERTIES GENERATED true)

	function(setup_ctags_target sources)
		foreach(directory IN LISTS sources)
			file(GLOB_RECURSE files "${directory}")
			list(APPEND source_files ${files})
		endforeach()
		string(REPLACE ";" "\n" source_files "${source_files}")
		file(WRITE "${CMAKE_BINARY_DIR}/cscope.files.in" "${source_files}")
		configure_file("${CMAKE_BINARY_DIR}/cscope.files.in" "${CMAKE_BINARY_DIR}/cscope.files" COPYONLY)

		add_custom_target(tags
			COMMAND ${CTAGS_PATH} --c++-kinds=+p --fields=+iaS --extras=+q -L ${CMAKE_BINARY_DIR}/cscope.files
			COMMAND ${CSCOPE_PATH} -b
			WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
			)
	endfunction()
endif()

