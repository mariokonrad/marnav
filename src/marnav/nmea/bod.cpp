#include "bod.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * bod::TAG;

bod::bod()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void bod::set_bearing_true(double t)
{
	bearing_true = t;
	type_true = reference::TRUE;
}

void bod::set_bearing_magn(double t)
{
	bearing_magn = t;
	type_magn = reference::MAGNETIC;
}

void bod::set_waypoint_to(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_to = id;
}

void bod::set_waypoint_from(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_from = id;
}

std::unique_ptr<sentence> bod::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in bod::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<bod>();
	result->set_talker(talker);
	bod & detail = static_cast<bod &>(*result);

	read(fields[0], detail.bearing_true);
	read(fields[1], detail.type_true);
	read(fields[2], detail.bearing_magn);
	read(fields[3], detail.type_magn);
	read(fields[4], detail.waypoint_to);
	read(fields[5], detail.waypoint_from);

	return result;
}

std::vector<std::string> bod::get_data() const
{
	return {to_string(bearing_true), to_string(type_true), to_string(bearing_magn),
		to_string(type_magn), to_string(waypoint_to), to_string(waypoint_from)};
}
}
}
