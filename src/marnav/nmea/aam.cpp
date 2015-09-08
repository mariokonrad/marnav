#include "aam.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * aam::TAG;

aam::aam()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
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
	arrival_circle_radius_unit = unit::distance::NM;
}

void aam::set_waypoint_id(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

void aam::check() const
{
	check_status(arrival_circle_entered, "arrival_circle_entered");
	check_status(perpendicualar_passed, "perpendicualar_passed");
	if (arrival_circle_radius && !arrival_circle_radius_unit)
		throw std::invalid_argument{"unit missing in sentence"};
	check_value(arrival_circle_radius_unit, {unit::distance::NM}, "arrival_circle_radius_unit");
}

std::unique_ptr<sentence> aam::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 5)
		throw std::invalid_argument{"invalid number of fields in aam::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<aam>();
	result->set_talker(talker);
	aam & detail = static_cast<aam &>(*result);

	read(fields[0], detail.arrival_circle_entered);
	read(fields[1], detail.perpendicualar_passed);
	read(fields[2], detail.arrival_circle_radius);
	read(fields[3], detail.arrival_circle_radius_unit);
	read(fields[4], detail.waypoint_id);

	detail.check();

	return result;
}

std::vector<std::string> aam::get_data() const
{
	return {to_string(arrival_circle_entered), to_string(perpendicualar_passed),
		to_string(arrival_circle_radius), to_string(arrival_circle_radius_unit),
		to_string(waypoint_id)};
}
}
}
