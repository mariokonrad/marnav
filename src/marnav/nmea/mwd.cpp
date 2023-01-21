#include <marnav/nmea/mwd.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav::nmea
{
constexpr sentence_id mwd::ID;
constexpr const char * mwd::TAG;

mwd::mwd()
	: sentence(ID, TAG, talker::weather_instruments)
{
}

mwd::mwd(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in mwd"};

	std::optional<reference> direction_true_ref;
	std::optional<reference> direction_mag_ref;
	std::optional<unit::velocity> speed_kn_unit;
	std::optional<unit::velocity> speed_ms_unit;

	read(*(first + 0), direction_true_);
	read(*(first + 1), direction_true_ref);
	read(*(first + 2), direction_mag_);
	read(*(first + 3), direction_mag_ref);
	read(*(first + 4), speed_kn_);
	read(*(first + 5), speed_kn_unit);
	read(*(first + 6), speed_ms_);
	read(*(first + 7), speed_ms_unit);

	check_value(direction_true_ref, {reference::TRUE}, "direction true ref");
	check_value(direction_mag_ref, {reference::MAGNETIC}, "direction magnetic ref");
	check_value(speed_kn_unit, {unit::velocity::knot}, "speed knot unit");
	check_value(speed_ms_unit, {unit::velocity::mps}, "speed meters pers second unit");
}

void mwd::set_direction_true(double t) noexcept
{
	direction_true_ = t;
}

void mwd::set_direction_mag(double t) noexcept
{
	direction_mag_ = t;
}

void mwd::set_speed_knots(units::velocity t) noexcept
{
	speed_kn_ = t.get<units::knots>();
}

void mwd::set_speed_mps(units::velocity t) noexcept
{
	speed_ms_ = t.get<units::meters_per_second>();
}

std::optional<units::velocity> mwd::get_speed_kn() const
{
	if (!speed_kn_)
		return {};
	return {*speed_kn_};
}

std::optional<units::velocity> mwd::get_speed_ms() const
{
	if (!speed_ms_)
		return {};
	return {*speed_ms_};
}

void mwd::append_data_to(std::string & s, const version &) const
{
	append(s, format(direction_true_, 1));
	append(s, to_string_if(reference::TRUE, direction_true_));
	append(s, format(direction_mag_, 1));
	append(s, to_string_if(reference::MAGNETIC, direction_mag_));
	append(s, format(speed_kn_, 1));
	append(s, to_string_if(unit::velocity::knot, speed_kn_));
	append(s, format(speed_ms_, 1));
	append(s, to_string_if(unit::velocity::mps, speed_ms_));
}
}
