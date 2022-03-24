#include <marnav/nmea/wdc.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id wdc::ID;
constexpr const char * wdc::TAG;

wdc::wdc()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

wdc::wdc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in wdc"};

	unit::distance distance_unit;

	read(*(first + 0), distance_);
	read(*(first + 1), distance_unit);
	read(*(first + 2), waypoint_id_);

	check_value(distance_unit, {unit::distance::nm}, "distance unit");
}

void wdc::set_distance(units::length t)
{
	distance_ = t.get<units::nautical_miles>();
	if (distance_.value() < 0.0)
		throw std::runtime_error{"negative distance"};
}

void wdc::append_data_to(std::string & s, const version &) const
{
	append(s, format(distance_, 1));
	append(s, to_string(unit::distance::nm));
	append(s, to_string(waypoint_id_));
}
}
}
