#include <marnav/nmea/vhw.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id vhw::ID;
constexpr const char * vhw::TAG;

vhw::vhw()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

vhw::vhw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in vhw"};

	utils::optional<reference> heading_true_ref;
	utils::optional<reference> heading_magn_ref;
	utils::optional<unit::velocity> speed_knots_unit;
	utils::optional<unit::velocity> speed_kmh_unit;

	read(*(first + 0), heading_true_);
	read(*(first + 1), heading_true_ref);
	read(*(first + 2), heading_magn_);
	read(*(first + 3), heading_magn_ref);
	read(*(first + 4), speed_knots_);
	read(*(first + 5), speed_knots_unit);
	read(*(first + 6), speed_kmh_);
	read(*(first + 7), speed_kmh_unit);

	check_value(heading_true_ref, {reference::TRUE}, "heading reference true");
	check_value(heading_magn_ref, {reference::MAGNETIC}, "heading reference magnetic");
	check_value(speed_knots_unit, {unit::velocity::knot}, "speed_knots_unit");
	check_value(speed_kmh_unit, {unit::velocity::kmh}, "speed_kmh_unit");
}

void vhw::set_heading_true(double t) noexcept
{
	heading_true_ = t;
}

void vhw::set_heading_magn(double t) noexcept
{
	heading_magn_ = t;
}

void vhw::set_speed_knots(units::velocity t) noexcept
{
	speed_knots_ = t.get<units::knots>();
}

void vhw::set_speed_kmh(units::velocity t) noexcept
{
	speed_kmh_ = t.get<units::kilometers_per_hour>();
}

void vhw::append_data_to(std::string & s) const
{
	append(s, to_string(heading_true_));
	append(s, to_string_if(reference::TRUE, heading_true_));
	append(s, to_string(heading_magn_));
	append(s, to_string_if(reference::MAGNETIC, heading_magn_));
	append(s, to_string(speed_knots_));
	append(s, to_string_if(unit::velocity::knot, speed_knots_));
	append(s, to_string(speed_kmh_));
	append(s, to_string_if(unit::velocity::kmh, speed_kmh_));
}
}
}
