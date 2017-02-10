#include "gga.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * gga::TAG;

gga::gga()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gga::gga(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 14)
		throw std::invalid_argument{"invalid number of fields in gga"};

	read(*(first + 0), time);
	read(*(first + 1), lat);
	read(*(first + 2), lat_hem);
	read(*(first + 3), lon);
	read(*(first + 4), lon_hem);
	read(*(first + 5), quality_indicator);
	read(*(first + 6), n_satellites);
	read(*(first + 7), hor_dilution);
	read(*(first + 8), altitude);
	read(*(first + 9), altitude_unit);
	read(*(first + 10), geodial_separation);
	read(*(first + 11), geodial_separation_unit);
	read(*(first + 12), dgps_age);
	read(*(first + 13), dgps_ref);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

utils::optional<geo::longitude> gga::get_longitude() const
{
	return (lon && lon_hem) ? lon : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> gga::get_latitude() const
{
	return (lat && lat_hem) ? lat : utils::optional<geo::latitude>{};
}

void gga::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void gga::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

std::vector<std::string> gga::get_data() const
{
	return {to_string(time), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(quality_indicator), to_string(n_satellites),
		to_string(hor_dilution), to_string(altitude), to_string(altitude_unit),
		to_string(geodial_separation), to_string(geodial_separation_unit), to_string(dgps_age),
		to_string(dgps_ref)};
}
}
}
