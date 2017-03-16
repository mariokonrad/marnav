set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(marnav-demo
	main.cpp
	)

target_include_directories(marnav-demo
	PRIVATE
		${marnav_INCLUDE_DIR}
	)

target_link_libraries(marnav-demo
	${marnav_LIBRARIES}
	)

