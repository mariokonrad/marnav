#ifndef MARNAV__NMEA__SPLIT__HPP
#define MARNAV__NMEA__SPLIT__HPP

#include <string>
#include <vector>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace detail
{
MARNAV_EXPORT std::vector<std::string> parse_fields(
	const std::string & s, const std::string::size_type start_pos = 1u);
}
/// @endcond
}
}

#endif
