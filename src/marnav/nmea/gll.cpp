#include "gll.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * gll::TAG;

gll::gll()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, mode_ind(mode_indicator::invalid)
{
}

gll::gll(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	// older version has no 'mode_indicator'
	const auto size = std::distance(first, last);
	if ((size < 6) || (size > 7))
		throw std::invalid_argument{
			std::string{"invalid number of fields in gll: expected 6, got "}
			+ std::to_string(size)};

	read(*(first + 0), lat);
	read(*(first + 1), lat_hem);
	read(*(first + 2), lon);
	read(*(first + 3), lon_hem);
	read(*(first + 4), time_utc);
	read(*(first + 5), data_valid);

	if (size > 6)
		read(*(first + 6), mode_ind);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

utils::optional<geo::longitude> gll::get_longitude() const
{
	return (lon && lon_hem) ? lon : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> gll::get_latitude() const
{
	return (lat && lat_hem) ? lat : utils::optional<geo::latitude>{};
}

void gll::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void gll::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void gll::append_data_to(std::string & s) const
{
	append(s, to_string(lat));
	append(s, to_string(lat_hem));
	append(s, to_string(lon));
	append(s, to_string(lon_hem));
	append(s, to_string(time_utc));
	append(s, to_string(data_valid));
	append(s, to_string(mode_ind));
}
}
}
