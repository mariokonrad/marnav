#include "gns.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(gns)

constexpr const char * gns::TAG;

gns::gns()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gns::gns(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 12)
		throw std::invalid_argument{"invalid number of fields in gns"};

	read(*(first + 0), time_utc);
	read(*(first + 1), lat);
	read(*(first + 2), lat_hem);
	read(*(first + 3), lon);
	read(*(first + 4), lon_hem);
	read(*(first + 5), mode_ind);
	read(*(first + 6), number_of_satellites);
	read(*(first + 7), hdrop);
	read(*(first + 8), antenna_altitude);
	read(*(first + 9), geodial_sepration);
	read(*(first + 10), age_of_differential_data);
	read(*(first + 11), differential_ref_station_id);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

utils::optional<geo::longitude> gns::get_longitude() const
{
	return (lon && lon_hem) ? lon : utils::optional<geo::longitude>{};
}

utils::optional<geo::latitude> gns::get_latitude() const
{
	return (lat && lat_hem) ? lat : utils::optional<geo::latitude>{};
}

void gns::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void gns::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void gns::set_mode_indicator(const std::string & t)
{
	if ((t.size() < 2) || (t.size() > 8))
		throw std::invalid_argument{"invalid mode indicator"};
	mode_ind = t;
}

std::vector<std::string> gns::get_data() const
{
	return {to_string(time_utc), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(mode_ind), to_string(number_of_satellites),
		to_string(hdrop), to_string(antenna_altitude), to_string(geodial_sepration),
		to_string(age_of_differential_data), to_string(differential_ref_station_id)};
}
}
}
