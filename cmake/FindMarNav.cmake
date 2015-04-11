# FindMarNav
# -----------
#
# Try to find the MarNav library
#
# Once done this will define
#
#   MARNAV_FOUND - System has MarNav
#   MARNAV_INCLUDE_DIR - The MarNav include directory
#   MARNAV_LIBRARIES - The libraries needed to use MarNav
#
#   MARNAV_ROOT - Can be set to install path

find_path(MARNAV_INCLUDE_DIR
	NAMES
		marnav/nmea/nmea.hpp
	HINTS
		${MARNAV_ROOT}/include
	PATH_SUFFIXES
		marnav
	)

