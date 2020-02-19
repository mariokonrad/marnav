#include <marnav/nmea/aam.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id aam::ID;
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

	unit::distance radius_unit;

	read(*(first + 0), arrival_circle_entered_);
	read(*(first + 1), perpendicualar_passed_);
	read(*(first + 2), arrival_circle_radius_);
	read(*(first + 3), radius_unit);
	read(*(first + 4), waypoint_id_);

	check_status(arrival_circle_entered_, "arrival_circle_entered");
	check_status(perpendicualar_passed_, "perpendicualar_passed");
	check_value(radius_unit, {unit::distance::nm}, "arrival_circle_radius_unit");
}

void aam::set_arrival_circle_entered(status s)
{
	check_status(s, "arrival_circle_entered");
	arrival_circle_entered_ = s;
}

void aam::set_perpendicular_passed(status s)
{
	check_status(s, "perpendicualar_passed");
	perpendicualar_passed_ = s;
}

void aam::set_arrival_circle_radius(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"invalid argument, arrival radius below zero"};
	arrival_circle_radius_ = t.get<units::nautical_miles>();
}

void aam::append_data_to(std::string & s) const
{
	append(s, to_string(arrival_circle_entered_));
	append(s, to_string(perpendicualar_passed_));
	append(s, to_string(arrival_circle_radius_.value()));
	append(s, to_string(unit::distance::nm));
	append(s, to_string(waypoint_id_));
}
}
}
