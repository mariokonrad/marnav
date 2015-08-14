#include "bww.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * bww::TAG;

bww::bww()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void bww::set_bearing_true(double t)
{
	bearing_true = t;
	bearing_true_ref = reference::TRUE;
}

void bww::set_bearing_mag(double t)
{
	bearing_mag = t;
	bearing_mag_ref = reference::MAGNETIC;
}

void bww::set_waypoint_to(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_to = id;
}

void bww::set_waypoint_from(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_from = id;
}

std::unique_ptr<sentence> bww::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in bww::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<bww>();
	result->set_talker(talker);
	bww & detail = static_cast<bww &>(*result);

	read(fields[0], detail.bearing_true);
	read(fields[1], detail.bearing_true_ref);
	read(fields[2], detail.bearing_mag);
	read(fields[3], detail.bearing_mag_ref);
	read(fields[4], detail.waypoint_to);
	read(fields[5], detail.waypoint_from);

	return result;
}

std::vector<std::string> bww::get_data() const
{
	return {to_string(bearing_true), to_string(bearing_true_ref), to_string(bearing_mag),
		to_string(bearing_mag_ref), to_string(waypoint_to), to_string(waypoint_from)};
}
}
}
