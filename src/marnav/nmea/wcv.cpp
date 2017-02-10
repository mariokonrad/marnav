#include "wcv.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * wcv::TAG;

wcv::wcv()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

wcv::wcv(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in wcv"};

	read(*(first + 0), speed);
	read(*(first + 1), speed_unit);
	read(*(first + 2), waypoint_id);
}

void wcv::set_speed(double t) noexcept
{
	speed = t;
	speed_unit = unit::velocity::knot;
}

std::vector<std::string> wcv::get_data() const
{
	return {format(speed, 1), to_string(speed_unit), to_string(waypoint_id)};
}
}
}
