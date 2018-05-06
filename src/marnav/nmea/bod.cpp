#include "bod.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * bod::TAG;

bod::bod()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

bod::bod(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in bod"};

	read(*(first + 0), bearing_true_);
	read(*(first + 1), type_true_);
	read(*(first + 2), bearing_magn_);
	read(*(first + 3), type_magn_);
	read(*(first + 4), waypoint_to_);
	read(*(first + 5), waypoint_from_);
}

void bod::set_bearing_true(double t) noexcept
{
	bearing_true_ = t;
	type_true_ = reference::TRUE_NORTH;
}

void bod::set_bearing_magn(double t) noexcept
{
	bearing_magn_ = t;
	type_magn_ = reference::MAGNETIC;
}

void bod::append_data_to(std::string & s) const
{
	append(s, to_string(bearing_true_));
	append(s, to_string(type_true_));
	append(s, to_string(bearing_magn_));
	append(s, to_string(type_magn_));
	append(s, to_string(waypoint_to_));
	append(s, to_string(waypoint_from_));
}
}
}
