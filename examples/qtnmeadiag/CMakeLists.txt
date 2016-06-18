
find_package(Qt5Core)

if(${Qt5Core_FOUND})
	find_package(Qt5Widgets REQUIRED)
	find_package(Qt5SerialPort REQUIRED)

	message(STATUS "Qt5 found: ${Qt5Core_VERSION}")
	message(STATUS "  ${Qt5Core_LIBRARIES}")
	message(STATUS "  ${Qt5Widgets_LIBRARIES}")
	message(STATUS "  ${Qt5SerialPort_LIBRARIES}")

	include_directories(${Qt5Core_INCLUDE_DIRS})
	include_directories(${Qt5Widgets_INCLUDE_DIRS})
	include_directories(${Qt5SerialPort_INCLUDE_DIRS})

	set(CMAKE_AUTOMOC ON)

	add_executable(qtnmeadiag
		MainWindow.cpp
		main.cpp
		)

	target_link_libraries(qtnmeadiag
		${Qt5SerialPort_LIBRARIES}
		${Qt5Widgets_LIBRARIES}
		${Qt5Core_LIBRARIES}
		marnav
		)

	qt5_use_modules(qtnmeadiag Core Widgets SerialPort)

else()
	message(STATUS "Qt5 not found")
endif()

