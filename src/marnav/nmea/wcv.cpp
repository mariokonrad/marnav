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

	read(*(first + 0), speed_);
	read(*(first + 1), speed_unit_);
	read(*(first + 2), waypoint_id_);
}

void wcv::set_speed(double t) noexcept
{
	speed_ = t;
	speed_unit_ = unit::velocity::knot;
}

void wcv::append_data_to(std::string & s) const
{
	append(s, format(speed_, 1));
	append(s, to_string(speed_unit_));
	append(s, to_string(waypoint_id_));
}
}
}
