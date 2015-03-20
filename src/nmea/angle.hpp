#ifndef __NMEA__ANGLE__HPP__
#define __NMEA__ANGLE__HPP__

#include <geo/angle.hpp>

namespace nmea
{
geo::angle parse_angle(const std::string& s) throw(std::invalid_argument);

geo::latitude parse_latitude(const std::string& s) throw(std::invalid_argument);
std::string to_string(const geo::latitude& v);

geo::longitude parse_longitude(const std::string& s) throw(std::invalid_argument);
std::string to_string(const geo::longitude& v);
}

#endif
