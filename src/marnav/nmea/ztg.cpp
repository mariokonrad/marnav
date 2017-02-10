#include "ztg.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * ztg::TAG;

ztg::ztg()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

ztg::ztg(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in ztg"};

	read(*(first + 0), time_utc);
	read(*(first + 1), time_remaining);
	read(*(first + 2), waypoint_id);
}

std::vector<std::string> ztg::get_data() const
{
	return {to_string(time_utc), to_string(time_remaining), to_string(waypoint_id)};
}
}
}
