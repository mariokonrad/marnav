#ifndef MARNAV__NMEA__CONSTANTS__HPP
#define MARNAV__NMEA__CONSTANTS__HPP

#include <cstdint>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// Enumeration of all possible directions.
enum class MARNAV_EXPORT direction : char {
	east, ///< NMEA representation: 'E'
	west, ///< NMEA representation: 'W'
	north, ///< NMEA representation: 'N'
	south, ///< NMEA representation: ' S'
	none ///< To silence the compiler
};

/// Status values used in NMEA.
enum class MARNAV_EXPORT status : char {
	ok, ///< NMEA representation: 'A'
	warning ///< NMEA representation: 'V'
};

/// Positioning System Mode Indicator constants.
enum class MARNAV_EXPORT mode_indicator : char {
	invalid, ///< NMEA representation: 'V'
	autonomous, ///< NMEA representation: 'A'
	differential, ///< NMEA representation: 'D'
	estimated, ///< NMEA representation: 'E'
	manual_input, ///< NMEA representation: 'M'
	simulated, ///< NMEA representation: 'S'
	data_not_valid, ///< NMEA representation: 'N'
	precise ///< NMEA representation: 'P'
};

/// Signal quality.
enum class MARNAV_EXPORT quality : uint32_t {
	invalid = 0, ///< NMEA representation: 0
	gps_fix = 1, ///< NMEA representation: 1
	dgps_fix = 2, ///< NMEA representation: 2
	guess = 6, ///< NMEA representation: 6
	simulation = 8 ///< NMEA representation: 8
};

/// Target status.
enum class MARNAV_EXPORT target_status : char {
	lost, ///< NMEA representation: 'L'
	query, ///< NMEA representation: 'Q'
	tracking ///< NMEA representation: 'T'
};

/// Contains enumerations of units.
namespace unit
{
/// Enumeration of unis of distance.
enum class MARNAV_EXPORT distance : char {
	meter, ///< NMEA representation: 'M'
	feet, ///< NMEA representation: 'f'
	nm, ///< NMEA representation: 'N' / nautical miles
	km, ///< NMEA representation: 'K' / kilometers
	fathom ///< NMEA representation: 'F'
};

/// Enumeration of unis of velocity.
enum class MARNAV_EXPORT velocity : char {
	knot, ///< NMEA representation: 'N'
	kmh, ///< NMEA representation: 'K' / kilometers per hour
	mps ///< NMEA representation: 'M' / meters per second
};

/// Enumeration of unis of temperature.
enum class MARNAV_EXPORT temperature : char {
	celsius ///< NMEA representation: 'C'
};

/// Enumeration of unis of pressure.
enum class MARNAV_EXPORT pressure : char {
	bar, ///< NMEA representation: 'B'
	Pa ///< NMEA representation: 'P'
};
}

/// Enumeration of all possible references of data.
enum class MARNAV_EXPORT reference : char {
	TRUE_NORTH, ///< NMEA representation: 'T'
	MAGNETIC, ///< NMEA representation: 'M'
	RELATIVE_NORTH ///< NMEA representation: 'R'
};

/// Side of the vessel.
enum class MARNAV_EXPORT side : char {
	left, ///< NMEA representation: 'L'
	right ///< NMEA Representation: 'R'
};

/// Status of routes.
enum class MARNAV_EXPORT route : char {
	complete, ///< NMEA representation: 'c'
	working ///< NMEA representation: 'w'
};

enum class MARNAV_EXPORT selection_mode : char {
	manual, ///< NMEA representation: 'M'
	automatic ///< NMEA representation: 'A'
};

enum class MARNAV_EXPORT ais_channel : char {
	A, ///< NMEA representation: 'A'
	B ///< NMEA representation: 'B'
};

enum class MARNAV_EXPORT type_of_point : char {
	collision, ///< NMEA representation: 'C'
	turning_point, ///< NMEA representation: 'T'
	reference, ///< NMEA representation: 'R'
	wheelover, ///< NMEA representation: 'W'
};
}
}

#endif
