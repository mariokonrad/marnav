#include "bww.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * bww::TAG;

bww::bww()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

bww::bww(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in bww"};

	read(*(first + 0), bearing_true);
	read(*(first + 1), bearing_true_ref);
	read(*(first + 2), bearing_mag);
	read(*(first + 3), bearing_mag_ref);
	read(*(first + 4), waypoint_to);
	read(*(first + 5), waypoint_from);
}

void bww::set_bearing_true(double t) noexcept
{
	bearing_true = t;
	bearing_true_ref = reference::TRUE;
}

void bww::set_bearing_mag(double t) noexcept
{
	bearing_mag = t;
	bearing_mag_ref = reference::MAGNETIC;
}

std::vector<std::string> bww::get_data() const
{
	return {to_string(bearing_true), to_string(bearing_true_ref), to_string(bearing_mag),
		to_string(bearing_mag_ref), to_string(waypoint_to), to_string(waypoint_from)};
}
}
}
