#include "aam.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * aam::TAG;

aam::aam()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

aam::aam(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in aam"};

	read(*(first + 0), arrival_circle_entered);
	read(*(first + 1), perpendicualar_passed);
	read(*(first + 2), arrival_circle_radius);
	read(*(first + 3), arrival_circle_radius_unit);
	read(*(first + 4), waypoint_id);

	check();
}

void aam::set_arrival_circle_entered(status s)
{
	check_status(s, "arrival_circle_entered");
	arrival_circle_entered = s;
}

void aam::set_perpendicular_passed(status s)
{
	check_status(s, "perpendicualar_passed");
	perpendicualar_passed = s;
}

void aam::set_arrival_circle_radius(double t)
{
	if (t < 0.0)
		throw std::invalid_argument{"invalid argument, arrival radius below zero"};
	arrival_circle_radius = t;
	arrival_circle_radius_unit = unit::distance::nm;
}

void aam::check() const
{
	check_status(arrival_circle_entered, "arrival_circle_entered");
	check_status(perpendicualar_passed, "perpendicualar_passed");
	if (arrival_circle_radius && !arrival_circle_radius_unit)
		throw std::invalid_argument{"unit missing in sentence"};
	check_value(arrival_circle_radius_unit, {unit::distance::nm}, "arrival_circle_radius_unit");
}

std::vector<std::string> aam::get_data() const
{
	return {to_string(arrival_circle_entered), to_string(perpendicualar_passed),
		to_string(arrival_circle_radius), to_string(arrival_circle_radius_unit),
		to_string(waypoint_id)};
}
}
}
