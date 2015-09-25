#ifndef __NMEA__CONSTANTS__HPP__
#define __NMEA__CONSTANTS__HPP__

#include <string>
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace nmea
{
enum class direction : char {
	east, ///< NMEA representation: 'E'
	west, ///< NMEA representation: 'W'
	north, ///< NMEA representation: 'N'
	south ///< NMEA representation: ' S'
};

enum class status : char {
	ok, ///< NMEA representation: 'A'
	warning ///< NMEA representation: 'V'
};

/// Positioning System Mode Indicator constants.
enum class positioning_system_mode_indicator : char {
	invalid, ///< NMEA representation: 'V'
	autonomous, ///< NMEA representation: 'A'
	differential, ///< NMEA representation: 'D'
	estimated, ///< NMEA representation: 'E'
	manual_input, ///< NMEA representation: 'M'
	simulated, ///< NMEA representation: 'S'
	data_not_valid, ///< NMEA representation: 'N'
	precise ///< NMEA representation: 'P'
};

enum class quality : uint32_t {
	invalid = 0, ///< NMEA representation: 0
	gps_fix = 1, ///< NMEA representation: 1
	dgps_fix = 2, ///< NMEA representation: 2
	guess = 6, ///< NMEA representation: 6
	simulation = 8 ///< NMEA representation: 8
};

namespace unit
{
enum class distance : char {
	meter, ///< NMEA representation: 'M'
	feet, ///< NMEA representation: 'f'
	nm, ///< NMEA representation: 'N' / nautical miles
	km, ///< NMEA representation: 'K' / kilometers
	fathom ///< NMEA representation: 'F'
};

enum class velocity : char {
	knot, ///< NMEA representation: 'N'
	kmh, ///< NMEA representation: 'K' / kilometers per hour
	mps ///< NMEA representation: 'M' / meters per second
};

enum class temperature : char {
	celsius ///< NMEA representation: 'C'
};

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

enum class side : char {
	left, ///< NMEA representation: 'L'
	right ///< NMEA Representation: 'R'
};

enum class route : char {
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

direction convert_hemisphere(const geo::latitude & p) noexcept;
direction convert_hemisphere(const geo::longitude & p) noexcept;
geo::latitude::hemisphere convert_hemisphere_lat(direction t);
geo::longitude::hemisphere convert_hemisphere_lon(direction t);
}
}

#endif
