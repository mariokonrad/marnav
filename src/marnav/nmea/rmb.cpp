#include "rmb.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * rmb::TAG;

rmb::rmb()
	: sentence(ID, TAG, talker_id::global_positioning_system)
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

std::unique_ptr<sentence> rmb::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	// before and after NMEA 2.3
	if ((fields.size() < 13) || (fields.size() > 14))
		throw std::invalid_argument{"invalid number of fields in rmb::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rmb>();
	result->set_talker(talker);
	rmb & detail = static_cast<rmb &>(*result);

	read(fields[0], detail.active);
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

	// NMEA 2.3 or newer
	if (fields.size() > 13)
		read(fields[12], detail.mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	if (detail.lat && detail.lat_hem)
		detail.lat->change_hemisphere(convert_hemisphere_lat(detail.lat_hem.value()));
	if (detail.lon && detail.lon_hem)
		detail.lon->change_hemisphere(convert_hemisphere_lon(detail.lon_hem.value()));

	return result;
}

std::vector<std::string> rmb::get_data() const
{
	return {to_string(active), to_string(cross_track_error), to_string(steer_dir),
		to_string(waypoint_to), to_string(waypoint_from), to_string(lat), to_string(lat_hem),
		to_string(lon), to_string(lon_hem), to_string(range), to_string(bearing),
		to_string(dst_velocity), to_string(arrival_status), to_string(mode_indicator)};
}
}
}
