#ifndef __MARNAV__NMEA__ANGLE__HPP__
#define __MARNAV__NMEA__ANGLE__HPP__

#include <string>
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace nmea
{
geo::latitude parse_latitude(const std::string & s);
std::string to_string(const geo::latitude & v);

geo::longitude parse_longitude(const std::string & s);
std::string to_string(const geo::longitude & v);
}
}

#endif
