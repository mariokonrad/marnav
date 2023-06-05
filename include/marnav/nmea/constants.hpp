#ifndef MARNAV_NMEA_CONSTANTS_HPP
#define MARNAV_NMEA_CONSTANTS_HPP

#include <cstdint>

namespace marnav::nmea
{
/// Enumeration of all possible directions.
enum class direction : char {
	east, ///< NMEA representation: 'E'
	west, ///< NMEA representation: 'W'
	north, ///< NMEA representation: 'N'
	south, ///< NMEA representation: ' S'
	none ///< To silence the compiler
};

/// Status values used in NMEA.
enum class status : char {
	ok, ///< NMEA representation: 'A'
	warning ///< NMEA representation: 'V'
};

/// Positioning System Mode Indicator constants.
enum class mode_indicator : char {
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
enum class quality : uint32_t {
	invalid = 0, ///< NMEA representation: 0
	gps_fix = 1, ///< NMEA representation: 1
	dgps_fix = 2, ///< NMEA representation: 2
	guess = 6, ///< NMEA representation: 6
	simulation = 8 ///< NMEA representation: 8
};

/// Target status.
enum class target_status : char {
	lost, ///< NMEA representation: 'L'
	query, ///< NMEA representation: 'Q'
	tracking ///< NMEA representation: 'T'
};

/// Contains enumerations of units.
namespace unit
{
/// Enumeration of unis of distance.
enum class distance : char {
	meter, ///< NMEA representation: 'M'
	feet, ///< NMEA representation: 'f'
	nm, ///< NMEA representation: 'N' / nautical miles
	km, ///< NMEA representation: 'K' / kilometers
	fathom ///< NMEA representation: 'F'
};

/// Enumeration of unis of velocity.
enum class velocity : char {
	knot, ///< NMEA representation: 'N'
	kmh, ///< NMEA representation: 'K' / kilometers per hour
	mps ///< NMEA representation: 'M' / meters per second
};

/// Enumeration of unis of temperature.
enum class temperature : char {
	celsius ///< NMEA representation: 'C'
};

/// Enumeration of unis of pressure.
enum class pressure : char {
	bar, ///< NMEA representation: 'B'
	pascal ///< NMEA representation: 'P'
};
}

/// Enumeration of all possible references of data.
enum class reference : char {
	TRUE, ///< NMEA representation: 'T'
	MAGNETIC, ///< NMEA representation: 'M'
	RELATIVE ///< NMEA representation: 'R'
};

/// Side of the vessel.
enum class side : char {
	left, ///< NMEA representation: 'L'
	right ///< NMEA Representation: 'R'
};

/// Status of routes.
enum class route_mode : char {
	complete, ///< NMEA representation: 'c'
	working ///< NMEA representation: 'w'
};

enum class selection_mode : char {
	manual, ///< NMEA representation: 'M'
	automatic ///< NMEA representation: 'A'
};

enum class ais_channel : char {
	A, ///< NMEA representation: 'A'
	B ///< NMEA representation: 'B'
};

enum class type_of_point : char {
	collision, ///< NMEA representation: 'C'
	turning_point, ///< NMEA representation: 'T'
	reference, ///< NMEA representation: 'R'
	wheelover, ///< NMEA representation: 'W'
};

enum class frequency_index : uint8_t {
	not_received_over_air = 0, ///< NMEA representation: 0
	f_490_khz = 1, ///< NMEA representation: 1 = 490 kHz
	f_518_khz = 2, ///< NMEA representation: 2 = 518 kHz
	f_4209_5_khz = 3, ///< NMEA representation: 3 = 4209.5 kHz
};
}

#endif
