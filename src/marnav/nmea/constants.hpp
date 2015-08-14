#ifndef __NMEA__CONSTANTS__HPP__
#define __NMEA__CONSTANTS__HPP__

#include <marnav/geo/angle.hpp>
#include <stdexcept>
#include <string>

namespace marnav
{
namespace nmea
{
enum class direction : char {
	EAST, ///< NMEA representation: 'E'
	WEST, ///< NMEA representation: 'W'
	NORTH, ///< NMEA representation: 'N'
	SOUTH ///< NMEA representation: ' S'
};

enum class status : char {
	OK, ///< NMEA representation: 'A'
	WARNING ///< NMEA representation: 'V'
};

/// Positioning System Mode Indicator constants.
enum class positioning_system_mode_indicator : char {
	INVALID, ///< NMEA representation: 'V'
	AUTONOMOUS, ///< NMEA representation: 'A'
	DIFFERENTIAL, ///< NMEA representation: 'D'
	ESTIMATED, ///< NMEA representation: 'E'
	MANUAL_INPUT, ///< NMEA representation: 'M'
	SIMULATED, ///< NMEA representation: 'S'
	DATA_NOT_VALID, ///< NMEA representation: 'N'
	PRECISE ///< NMEA representation: 'P'
};

enum class quality : uint32_t {
	INVALID = 0, ///< NMEA representation: 0
	GPS_FIX = 1, ///< NMEA representation: 1
	DPGS_FIX = 2, ///< NMEA representation: 2
	GUESS = 6, ///< NMEA representation: 6
	SIMULATION = 8 ///< NMEA representation: 8
};

namespace unit
{
enum class distance : char {
	METER, ///< NMEA representation: 'M'
	FEET, ///< NMEA representation: 'f'
	NM, ///< NMEA representation: 'N' / nautical miles
	KM, ///< NMEA representation: 'K' / kilometers
	FATHOM ///< NMEA representation: 'F'
};

enum class velocity : char {
	KNOT, ///< NMEA representation: 'N'
	KMH, ///< NMEA representation: 'K' / kilometers per hour
	MPS ///< NMEA representation: 'M' / meters per second
};

enum class temperature : char {
	CELSIUS ///< NMEA representation: 'C'
};

enum class pressure : char {
	BAR, ///< NMEA representation: 'B'
	PASCAL ///< NMEA representation: 'P'
};
}

/// Enumeration of all possible references of data.
enum class reference : char {
	TRUE, ///< NMEA representation: 'T'
	MAGNETIC, ///< NMEA representation: 'M'
	RELATIVE ///< NMEA representation: 'R'
};

enum class side : char {
	LEFT, ///< NMEA representation: 'L'
	RIGHT ///< NMEA Representation: 'R'
};

enum class route : char {
	COMPLETE, ///< NMEA representation: 'c'
	WORKING ///< NMEA representation: 'w'
};

enum class selection_mode : char {
	MANUAL, ///< NMEA representation: 'M'
	AUTOMATIC ///< NMEA representation: 'A'
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

direction convert_hemisphere(const geo::latitude & p);
direction convert_hemisphere(const geo::longitude & p);
geo::latitude::hemisphere convert_hemisphere_lat(direction t) throw(std::invalid_argument);
geo::longitude::hemisphere convert_hemisphere_lon(direction t) throw(std::invalid_argument);
}
}

#endif
