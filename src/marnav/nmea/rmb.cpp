#include "rmb.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

rmb::rmb()
	: sentence(ID, "RMB", talker_id::global_positioning_system)
{
}

void rmb::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void rmb::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void rmb::set_waypoint_to(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_to = id;
}

void rmb::set_waypoint_from(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_from = id;
}

void rmb::check_waypoint_id(const std::string & id) const throw(std::invalid_argument)
{
	if (id.size() > 8)
		throw std::invalid_argument{"string size to large, only 8 characters allowed for id"};
}

std::unique_ptr<sentence> rmb::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 13)
		throw std::invalid_argument{"invalid number of fields in rmb::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rmb>();
	result->set_talker(talker);
	rmb & detail = static_cast<rmb &>(*result);

	read(fields[0], detail.status);
	read(fields[1], detail.cross_track_error);
	read(fields[2], detail.steer_dir);
	read(fields[3], detail.waypoint_to);
	read(fields[4], detail.waypoint_from);
	read(fields[5], detail.lat);
	read(fields[6], detail.lat_hem);
	read(fields[7], detail.lon);
	read(fields[8], detail.lon_hem);
	read(fields[9], detail.range);
	read(fields[10], detail.bearing);
	read(fields[11], detail.dst_velocity);
	read(fields[12], detail.arrival_status);

	return result;
}

std::vector<std::string> rmb::get_data() const
{
	return {
		to_string(status), to_string(cross_track_error), to_string(steer_dir),
		to_string(waypoint_to), to_string(waypoint_from), to_string(lat), to_string(lat_hem),
		to_string(lon), to_string(lon_hem), to_string(range), to_string(bearing),
		to_string(dst_velocity), to_string(arrival_status),
	};
}
}
}

