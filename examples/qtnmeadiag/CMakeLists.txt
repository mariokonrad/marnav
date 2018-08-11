
find_package(Qt5Core)

if(${Qt5Core_FOUND})
	find_package(Qt5Widgets REQUIRED)
	find_package(Qt5SerialPort REQUIRED)

	message(STATUS "Qt5 found: ${Qt5Core_VERSION}")
	message(STATUS "  ${Qt5Core_LIBRARIES}")
	message(STATUS "  ${Qt5Widgets_LIBRARIES}")
	message(STATUS "  ${Qt5SerialPort_LIBRARIES}")

	set(CMAKE_AUTOMOC ON)

	add_executable(qtnmeadiag
		MainWindow.cpp
		main.cpp
		)

	target_link_libraries(qtnmeadiag Qt5::SerialPort Qt5::Widgets Qt5::Core marnav)

else()
	message(STATUS "Qt5 not found")
endif()

