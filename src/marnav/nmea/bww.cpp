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

void bww::append_data_to(std::string & s) const
{
	append(s, to_string(bearing_true));
	append(s, to_string(bearing_true_ref));
	append(s, to_string(bearing_mag));
	append(s, to_string(bearing_mag_ref));
	append(s, to_string(waypoint_to));
	append(s, to_string(waypoint_from));
}
}
}
