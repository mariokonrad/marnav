#include "rmb.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>
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
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	// before and after NMEA 2.3
	const auto size = std::distance(first, last);
	if ((size < 13) || (size > 14))
		throw std::invalid_argument{"invalid number of fields in rmb::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rmb>();
	result->set_talker(talker);
	rmb & detail = static_cast<rmb &>(*result);

	read(*(first + 0), detail.active);
	read(*(first + 1), detail.cross_track_error);
	read(*(first + 2), detail.steer_dir);
	read(*(first + 3), detail.waypoint_to);
	read(*(first + 4), detail.waypoint_from);
	read(*(first + 5), detail.lat);
	read(*(first + 6), detail.lat_hem);
	read(*(first + 7), detail.lon);
	read(*(first + 8), detail.lon_hem);
	read(*(first + 9), detail.range);
	read(*(first + 10), detail.bearing);
	read(*(first + 11), detail.dst_velocity);
	read(*(first + 12), detail.arrival_status);

	// NMEA 2.3 or newer
	if (size > 13)
		read(*(first + 12), detail.mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	detail.lat = correct_hemisphere(detail.lat, detail.lat_hem);
	detail.lon = correct_hemisphere(detail.lon, detail.lon_hem);

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
