#include "bwr.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * bwr::TAG;

bwr::bwr()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

bwr::bwr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto n = std::distance(first, last);
	if ((n < 12) || (n > 13))
		throw std::invalid_argument{"invalid number of fields in bwr"};

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

	if (n > 12)
		read(*(first + 12), mode_ind);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

utils::optional<geo::longitude> bwr::get_longitude() const
{
	return (lon && lon_hem) ? lon : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> bwr::get_latitude() const
{
	return (lat && lat_hem) ? lat : utils::optional<geo::latitude>{};
}

void bwr::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void bwr::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void bwr::set_bearing_true(double t) noexcept
{
	bearing_true = t;
	bearing_true_ref = reference::TRUE;
}

void bwr::set_bearing_mag(double t) noexcept
{
	bearing_mag = t;
	bearing_mag_ref = reference::MAGNETIC;
}

void bwr::set_distance(double t) noexcept
{
	distance = t;
	distance_unit = unit::distance::nm;
}

void bwr::append_data_to(std::string & s) const
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
