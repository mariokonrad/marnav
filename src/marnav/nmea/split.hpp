#ifndef MARNAV_NMEA_SPLIT_HPP
#define MARNAV_NMEA_SPLIT_HPP

#include <string>
#include <vector>

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace detail
{
std::vector<std::string> parse_fields(
	const std::string & s, const std::string::size_type start_pos = 1u);
}
/// @endcond
}
}

#endif
