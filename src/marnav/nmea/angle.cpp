#include "angle.hpp"
#include <stdexcept>
#include <cmath>

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace
{
static geo::angle parse_angle(const std::string & s)
{
	if (s.empty())
		return geo::angle{0.0};
	std::size_t pos = 0;
	auto tmp = std::stod(s, &pos);
	if (pos != s.size())
		throw std::invalid_argument{"invalid string for conversion to geo::angle for NMEA"};

	// adoption of NMEA angle DDDMM.SSS to the one that is used here
	const double deg = (tmp - fmod(tmp, 100.0)) / 100.0;
	const double min = (tmp - (deg * 100.0)) / 60.0;

	if (std::abs(min) >= 1.0)
		throw std::invalid_argument{"invalid format for minutes in geo::angle for NMEA"};

	return geo::angle{deg + min};
}
}
/// @endcond

/// Returns the latitude, representing the specified string. The provided string is assumed
/// to be in the form specified by the NMEA standard.
///
/// @param[in] s The string containing latitude information.
/// @return The parsed latitude.
/// @exception std::invalid_argument The string is malfomred.
///
/// Example:
/// @code
///   auto lat = nmea::parse_latitude("37.0000");
/// @endcode
geo::latitude parse_latitude(const std::string & s)
{
	return geo::latitude{parse_angle(s)};
}

/// Returns the string representation of a latitude, in the form specified by the NMEA
/// standard.
///
/// @param[in] v The latitude.
/// @return A string that represents the latitude.
std::string to_string(const geo::latitude & v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%02u%02u.%04u", v.degrees(), v.minutes(),
		static_cast<uint32_t>((v.seconds() / 60) * 10000));
	return buf;
}

/// Returns the longitude, representing the specified string. The provided string is assumed
/// to be in the form specified by the NMEA standard.
///
/// @param[in] s The string containing latitude information.
/// @return The parsed longitude.
/// @exception std::invalid_argument The string is malfomred.
///
/// Example:
/// @code
///   auto lon = nmea::parse_longitude("002.3456");
/// @endcode
geo::longitude parse_longitude(const std::string & s)
{
	return geo::longitude{parse_angle(s)};
}

/// Returns the string representation of a longitude, in the form specified by the NMEA
/// standard.
///
/// @param[in] v The longitude.
/// @return A string that represents the longitude.
std::string to_string(const geo::longitude & v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%03u%02u.%04u", v.degrees(), v.minutes(),
		static_cast<uint32_t>(10000 * v.seconds() / 60));
	return buf;
}
}
}
