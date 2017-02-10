#include "hfb.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * hfb::TAG;

hfb::hfb()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

hfb::hfb(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in hfb"};

	read(*(first + 0), distance_head_foot);
	read(*(first + 1), distance_head_foot_unit);
	read(*(first + 2), distance_head_bottom);
	read(*(first + 3), distance_head_bottom_unit);
}

std::vector<std::string> hfb::get_data() const
{
	return {to_string(distance_head_foot), to_string(distance_head_foot_unit),
		to_string(distance_head_bottom), to_string(distance_head_bottom_unit)};
}
}
}
