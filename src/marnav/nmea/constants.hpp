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

namespace quality
{
constexpr const int INVALID = 0;
constexpr const int GPS_FIX = 1;
constexpr const int DPGS_FIX = 2;
constexpr const int GUESS = 6;
}

namespace unit
{
constexpr const char METER = 'M';
constexpr const char FEET = 'f';
constexpr const char NM = 'N'; // nautical miles
constexpr const char KM = 'K'; // kilometers
constexpr const char FATHOM = 'F';
constexpr const char KNOT = 'N';
constexpr const char KMH = 'K'; // kilometers per hour
constexpr const char MPS = 'M'; // meters per second
constexpr const char CELSIUS = 'C';
constexpr const char BAR = 'B'; // pressure in Bar
constexpr const char PASCAL = 'P'; // pressure in Pascal
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
