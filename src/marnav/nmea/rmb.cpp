#include "rmb.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(rmb)

constexpr const char * rmb::TAG;

rmb::rmb()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

rmb::rmb(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	// before and after NMEA 2.3
	const auto size = std::distance(first, last);
	if ((size < 13) || (size > 14))
		throw std::invalid_argument{"invalid number of fields in rmb"};

	read(*(first + 0), active);
	read(*(first + 1), cross_track_error);
	read(*(first + 2), steer_dir);
	read(*(first + 3), waypoint_to);
	read(*(first + 4), waypoint_from);
	read(*(first + 5), lat);
	read(*(first + 6), lat_hem);
	read(*(first + 7), lon);
	read(*(first + 8), lon_hem);
	read(*(first + 9), range);
	read(*(first + 10), bearing);
	read(*(first + 11), dst_velocity);
	read(*(first + 12), arrival_status);

	// NMEA 2.3 or newer
	if (size > 13)
		read(*(first + 12), mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

utils::optional<geo::longitude> rmb::get_longitude() const
{
	return (lon && lon_hem) ? lon : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> rmb::get_latitude() const
{
	return (lat && lat_hem) ? lat : utils::optional<geo::latitude>{};
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

std::vector<std::string> rmb::get_data() const
{
	return {to_string(active), to_string(cross_track_error), to_string(steer_dir),
		to_string(waypoint_to), to_string(waypoint_from), to_string(lat), to_string(lat_hem),
		to_string(lon), to_string(lon_hem), to_string(range), to_string(bearing),
		to_string(dst_velocity), to_string(arrival_status), to_string(mode_indicator)};
}
}
}
