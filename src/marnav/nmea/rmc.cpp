#include "rmc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * rmc::TAG;

rmc::rmc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
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
	// before and after NMEA 2.3
	const auto size = std::distance(first, last);
	if ((size < 11) || (size > 12))
		throw std::invalid_argument{"invalid number of fields in rmc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rmc>();
	result->set_talker(talker);
	rmc & detail = static_cast<rmc &>(*result);

	read(*(first + 0), detail.time_utc);
	read(*(first + 1), detail.status);
	read(*(first + 2), detail.lat);
	read(*(first + 3), detail.lat_hem);
	read(*(first + 4), detail.lon);
	read(*(first + 5), detail.lon_hem);
	read(*(first + 6), detail.sog);
	read(*(first + 7), detail.heading);
	read(*(first + 8), detail.date);
	read(*(first + 9), detail.mag);
	read(*(first + 10), detail.mag_hem);

	// NMEA 2.3 or newer
	if (size > 11)
		read(*(first + 11), detail.mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	detail.lat = correct_hemisphere(detail.lat, detail.lat_hem);
	detail.lon = correct_hemisphere(detail.lon, detail.lon_hem);

	return result;
}

std::vector<std::string> rmc::get_data() const
{
	return {to_string(time_utc), to_string(status), to_string(lat), to_string(lat_hem),
		to_string(lon), to_string(lon_hem), to_string(sog), to_string(heading), to_string(date),
		to_string(mag), to_string(mag_hem), to_string(mode_indicator)};
}
}
}
