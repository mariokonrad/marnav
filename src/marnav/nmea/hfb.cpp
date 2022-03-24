#include <marnav/nmea/hfb.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id hfb::ID;
constexpr const char * hfb::TAG;

hfb::hfb()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

hfb::hfb(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in hfb"};

	unit::distance distance_head_foot_unit;
	unit::distance distance_head_bottom_unit;

	read(*(first + 0), distance_head_foot_);
	read(*(first + 1), distance_head_foot_unit);
	read(*(first + 2), distance_head_bottom_);
	read(*(first + 3), distance_head_bottom_unit);

	check_value(distance_head_foot_unit, {unit::distance::meter}, "distance head foot unit");
	check_value(
		distance_head_bottom_unit, {unit::distance::meter}, "distance head bottom unit");
}

void hfb::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(distance_head_foot_));
	append(s, to_string(unit::distance::meter));
	append(s, to_string(distance_head_bottom_));
	append(s, to_string(unit::distance::meter));
}
}
}
