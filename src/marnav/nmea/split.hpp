#ifndef __MARNAV__NMEA__SPLIT__HPP__
#define __MARNAV__NMEA__SPLIT__HPP__

#include <string>
#include <vector>

namespace marnav
{
namespace nmea
{
namespace detail
{
std::vector<std::string> parse_fields(const std::string & s);
}
}
}

#endif
