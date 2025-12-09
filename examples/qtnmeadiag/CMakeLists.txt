find_package(Qt5
	COMPONENTS
		Core
		Widgets
		SerialPort
	HINTS
		$ENV{QTHOME}
	)

if(TARGET Qt5::Core)
	find_package(Qt5Widgets REQUIRED)
	find_package(Qt5SerialPort REQUIRED)

	message(STATUS "Qt5 found: ${Qt5Core_VERSION}")
	message(STATUS "  ${Qt5Core_LIBRARIES}")
	message(STATUS "  ${Qt5Widgets_LIBRARIES}")
	message(STATUS "  ${Qt5SerialPort_LIBRARIES}")

	set(CMAKE_AUTOMOC ON)

	add_executable(qtnmeadiag)

	target_sources(qtnmeadiag
		PRIVATE
			MainWindow.cpp
			main.cpp
		)

	target_link_libraries(qtnmeadiag
		PRIVATE
			Qt5::Core
			Qt5::SerialPort
			Qt5::Widgets
			marnav::marnav
		)

else()
	message(STATUS "Qt5 not found")
endif()

