#include "aam.hpp"
#include "io.hpp"
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

void aam::set_arrival_circle_radius(double t)
{
	arrival_circle_radius = t;
	arrival_circle_radius_unit = unit::NM;
}

void aam::set_waypoint_id(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

void aam::check() const throw(std::invalid_argument)
{
	if (arrival_circle_entered)
		check_status(arrival_circle_entered.value());
	if (perpendicualar_passed)
		check_status(perpendicualar_passed.value());
	if (arrival_circle_radius && !arrival_circle_radius_unit)
		throw std::invalid_argument{"unit missing in sentence"};
	if (arrival_circle_radius_unit && arrival_circle_radius_unit.value() != unit::NM)
		throw std::invalid_argument{"invalid unit in sentence"};
}

std::unique_ptr<sentence> aam::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
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
