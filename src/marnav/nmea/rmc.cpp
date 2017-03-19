#include "rmc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * rmc::TAG;

rmc::rmc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

rmc::rmc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	// before and after NMEA 2.3
	const auto size = std::distance(first, last);
	if ((size < 11) || (size > 12))
		throw std::invalid_argument{"invalid number of fields in rmc"};

	read(*(first + 0), time_utc);
	read(*(first + 1), status);
	read(*(first + 2), lat);
	read(*(first + 3), lat_hem);
	read(*(first + 4), lon);
	read(*(first + 5), lon_hem);
	read(*(first + 6), sog);
	read(*(first + 7), heading);
	read(*(first + 8), date);
	read(*(first + 9), mag);
	read(*(first + 10), mag_hem);

	// NMEA 2.3 or newer
	if (size > 11)
		read(*(first + 11), mode_ind);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

utils::optional<geo::longitude> rmc::get_longitude() const
{
	return (lon && lon_hem) ? lon : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> rmc::get_latitude() const
{
	return (lat && lat_hem) ? lat : utils::optional<geo::latitude>{};
}

void rmc::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void rmc::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void rmc::set_mag(double t, direction h)
{
	check_value(h, {direction::east, direction::west}, "mag var hemisphere");
	mag = t;
	mag_hem = h;
}

void rmc::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc));
	append(s, to_string(status));
	append(s, to_string(lat));
	append(s, to_string(lat_hem));
	append(s, to_string(lon));
	append(s, to_string(lon_hem));
	append(s, to_string(sog));
	append(s, to_string(heading));
	append(s, to_string(date));
	append(s, to_string(mag));
	append(s, to_string(mag_hem));
	append(s, to_string(mode_ind));
}
}
}
