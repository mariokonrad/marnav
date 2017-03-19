#include "rmb.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * rmb::TAG;

rmb::rmb()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

rmb::rmb(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
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
		read(*(first + 13), mode_ind);

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

void rmb::append_data_to(std::string & s) const
{
	append(s, to_string(active));
	append(s, to_string(cross_track_error));
	append(s, to_string(steer_dir));
	append(s, to_string(waypoint_to));
	append(s, to_string(waypoint_from));
	append(s, to_string(lat));
	append(s, to_string(lat_hem));
	append(s, to_string(lon));
	append(s, to_string(lon_hem));
	append(s, to_string(range));
	append(s, to_string(bearing));
	append(s, to_string(dst_velocity));
	append(s, to_string(arrival_status));
	append(s, to_string(mode_ind));
}
}
}
