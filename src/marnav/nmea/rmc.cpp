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

rmc::rmc(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
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
		read(*(first + 11), mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
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

std::unique_ptr<sentence> rmc::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<rmc>(new rmc(talker, first, last));
}

std::vector<std::string> rmc::get_data() const
{
	return {to_string(time_utc), to_string(status), to_string(lat), to_string(lat_hem),
		to_string(lon), to_string(lon_hem), to_string(sog), to_string(heading), to_string(date),
		to_string(mag), to_string(mag_hem), to_string(mode_indicator)};
}
}
}
