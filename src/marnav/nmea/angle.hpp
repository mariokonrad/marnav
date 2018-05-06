#ifndef MARNAV__NMEA__ANGLE__HPP
#define MARNAV__NMEA__ANGLE__HPP

#include <string>
#include <marnav/geo/angle.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
MARNAV_EXPORT geo::latitude parse_latitude(const std::string & s);
MARNAV_EXPORT std::string to_string(const geo::latitude & v);

MARNAV_EXPORT geo::longitude parse_longitude(const std::string & s);
MARNAV_EXPORT std::string to_string(const geo::longitude & v);
}
}

#endif
