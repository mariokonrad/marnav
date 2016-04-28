#include "gns.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * gns::TAG;

gns::gns()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
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
	check_waypoint_id(t); // same requirements as waypoint IDs
	mode_indicator = t;
}

std::unique_ptr<sentence> gns::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 12)
		throw std::invalid_argument{"invalid number of fields in gns::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gns>();
	result->set_talker(talker);
	gns & detail = static_cast<gns &>(*result);

	read(*(first + 0), detail.time_utc);
	read(*(first + 1), detail.lat);
	read(*(first + 2), detail.lat_hem);
	read(*(first + 3), detail.lon);
	read(*(first + 4), detail.lon_hem);
	read(*(first + 5), detail.mode_indicator);
	read(*(first + 6), detail.number_of_satellites);
	read(*(first + 7), detail.hdrop);
	read(*(first + 8), detail.antenna_altitude);
	read(*(first + 9), detail.geodial_sepration);
	read(*(first + 10), detail.age_of_differential_data);
	read(*(first + 11), detail.differential_ref_station_id);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	detail.lat = correct_hemisphere(detail.lat, detail.lat_hem);
	detail.lon = correct_hemisphere(detail.lon, detail.lon_hem);

	return result;
}

std::vector<std::string> gns::get_data() const
{
	return {to_string(time_utc), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(mode_indicator), to_string(number_of_satellites),
		to_string(hdrop), to_string(antenna_altitude), to_string(geodial_sepration),
		to_string(age_of_differential_data), to_string(differential_ref_station_id)};
}
}
}
