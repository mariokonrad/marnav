#ifndef MARNAV_NMEA_ANGLE_HPP
#define MARNAV_NMEA_ANGLE_HPP

#include <marnav/geo/angle.hpp>
#include <string>

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
