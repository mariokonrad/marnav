#include <marnav/nmea/vpw.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id vpw::ID;
constexpr const char * vpw::TAG;

vpw::vpw()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

vpw::vpw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in vpw"};

	unit::velocity speed_knots_unit;
	unit::velocity speed_mps_unit;

	read(*(first + 0), speed_knots_);
	read(*(first + 1), speed_knots_unit);
	read(*(first + 2), speed_mps_);
	read(*(first + 3), speed_mps_unit);

	check_value(speed_knots_unit, {unit::velocity::knot}, "speed knots unit");
	check_value(speed_mps_unit, {unit::velocity::mps}, "speed mps unit");
}

void vpw::set_speed_knots(units::velocity t) noexcept
{
	speed_knots_ = t.get<units::knots>();
}

void vpw::set_speed_mps(units::velocity t) noexcept
{
	speed_mps_ = t.get<units::meters_per_second>();
}

std::optional<units::knots> vpw::get_speed_knots() const
{
	if (!speed_knots_)
		return {};
	return {*speed_knots_};
}

std::optional<units::meters_per_second> vpw::get_speed_meters_per_second() const
{
	if (!speed_mps_)
		return {};
	return {*speed_mps_};
}

void vpw::append_data_to(std::string & s) const
{
	append(s, to_string(speed_knots_));
	append(s, to_string_if(unit::velocity::knot, speed_knots_));
	append(s, to_string(speed_mps_));
	append(s, to_string_if(unit::velocity::mps, speed_mps_));
}
}
}
