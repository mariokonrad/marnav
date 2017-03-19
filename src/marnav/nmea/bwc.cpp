#include "bwc.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * bwc::TAG;

bwc::bwc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

bwc::bwc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size != 12) && (size != 13))
		throw std::invalid_argument{"invalid number of fields in bwc"};

	read(*(first + 0), time_utc);
	read(*(first + 1), lat);
	read(*(first + 2), lat_hem);
	read(*(first + 3), lon);
	read(*(first + 4), lon_hem);
	read(*(first + 5), bearing_true);
	read(*(first + 6), bearing_true_ref);
	read(*(first + 7), bearing_mag);
	read(*(first + 8), bearing_mag_ref);
	read(*(first + 9), distance);
	read(*(first + 10), distance_unit);
	read(*(first + 11), waypoint_id);

	if (size == 13)
		read(*(first + 12), mode_ind);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

utils::optional<geo::longitude> bwc::get_longitude() const
{
	return (lon && lon_hem) ? lon : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> bwc::get_latitude() const
{
	return (lat && lat_hem) ? lat : utils::optional<geo::latitude>{};
}

void bwc::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void bwc::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void bwc::set_bearing_true(double t) noexcept
{
	bearing_true = t;
	bearing_true_ref = reference::TRUE;
}

void bwc::set_bearing_mag(double t) noexcept
{
	bearing_mag = t;
	bearing_mag_ref = reference::MAGNETIC;
}

void bwc::set_distance(double t) noexcept
{
	distance = t;
	distance_unit = unit::distance::nm;
}

void bwc::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc));
	append(s, to_string(lat));
	append(s, to_string(lat_hem));
	append(s, to_string(lon));
	append(s, to_string(lon_hem));
	append(s, to_string(bearing_true));
	append(s, to_string(bearing_true_ref));
	append(s, to_string(bearing_mag));
	append(s, to_string(bearing_mag_ref));
	append(s, to_string(distance));
	append(s, to_string(distance_unit));
	append(s, to_string(waypoint_id));
	append(s, to_string(mode_ind));
}
}
}
