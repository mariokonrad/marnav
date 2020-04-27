#include <marnav/nmea/vwr.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id vwr::ID;
constexpr const char * vwr::TAG;

vwr::vwr()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

vwr::vwr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in vwr"};

	utils::optional<unit::velocity> speed_knots_unit;
	utils::optional<unit::velocity> speed_mps_unit;
	utils::optional<unit::velocity> speed_kmh_unit;

	read(*(first + 0), angle_);
	read(*(first + 1), angle_side_);
	read(*(first + 2), speed_knots_);
	read(*(first + 3), speed_knots_unit);
	read(*(first + 4), speed_mps_);
	read(*(first + 5), speed_mps_unit);
	read(*(first + 6), speed_kmh_);
	read(*(first + 7), speed_kmh_unit);

	check_value(speed_knots_unit, {unit::velocity::knot}, "speed knot unit");
	check_value(speed_mps_unit, {unit::velocity::mps}, "speed mps unit");
	check_value(speed_kmh_unit, {unit::velocity::kmh}, "speed kmh unit");
}

void vwr::set_angle(double angle, side s) noexcept
{
	angle_ = angle;
	angle_side_ = s;
}

void vwr::set_speed_knots(units::velocity t) noexcept
{
	speed_knots_ = t.get<units::knots>();
}

void vwr::set_speed_mps(units::velocity t) noexcept
{
	speed_mps_ = t.get<units::meters_per_second>();
}

void vwr::set_speed_kmh(units::velocity t) noexcept
{
	speed_kmh_ = t.get<units::kilometers_per_hour>();
}

utils::optional<units::velocity> vwr::get_speed_knots() const
{
	if (!speed_knots_)
		return {};
	return {*speed_knots_};
}

utils::optional<units::velocity> vwr::get_speed_mps() const
{
	if (!speed_mps_)
		return {};
	return {*speed_mps_};
}

utils::optional<units::velocity> vwr::get_speed_kmh() const
{
	if (!speed_kmh_)
		return {};
	return {*speed_kmh_};
}

void vwr::append_data_to(std::string & s) const
{
	append(s, to_string(angle_));
	append(s, to_string(angle_side_));
	append(s, to_string(speed_knots_));
	append(s, to_string_if(unit::velocity::knot, speed_knots_));
	append(s, to_string(speed_mps_));
	append(s, to_string_if(unit::velocity::mps, speed_mps_));
	append(s, to_string(speed_kmh_));
	append(s, to_string_if(unit::velocity::kmh, speed_kmh_));
}
}
}
