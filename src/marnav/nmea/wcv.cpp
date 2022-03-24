#include <marnav/nmea/wcv.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id wcv::ID;
constexpr const char * wcv::TAG;

wcv::wcv()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

wcv::wcv(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in wcv"};

	std::optional<unit::velocity> speed_unit;

	read(*(first + 0), speed_);
	read(*(first + 1), speed_unit);
	read(*(first + 2), waypoint_id_);

	check_value(speed_unit, {unit::velocity::knot}, "speed unit");
}

void wcv::set_speed(units::velocity t) noexcept
{
	speed_ = t.get<units::knots>();
}

std::optional<units::velocity> wcv::get_speed() const
{
	if (!speed_)
		return {};
	return {*speed_};
}

void wcv::append_data_to(std::string & s, const version &) const
{
	append(s, format(speed_, 1));
	append(s, to_string_if(unit::velocity::knot, speed_));
	append(s, to_string(waypoint_id_));
}
}
}
