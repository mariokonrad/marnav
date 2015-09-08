#include "gns.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
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
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 12)
		throw std::invalid_argument{"invalid number of fields in gns::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gns>();
	result->set_talker(talker);
	gns & detail = static_cast<gns &>(*result);

	read(fields[0], detail.time_utc);
	read(fields[1], detail.lat);
	read(fields[2], detail.lat_hem);
	read(fields[3], detail.lon);
	read(fields[4], detail.lon_hem);
	read(fields[5], detail.mode_indicator);
	read(fields[6], detail.number_of_satellites);
	read(fields[7], detail.hdrop);
	read(fields[8], detail.antenna_altitude);
	read(fields[9], detail.geodial_sepration);
	read(fields[10], detail.age_of_differential_data);
	read(fields[11], detail.differential_ref_station_id);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	if (detail.lat && detail.lat_hem)
		detail.lat->change_hemisphere(convert_hemisphere_lat(detail.lat_hem.value()));
	if (detail.lon && detail.lon_hem)
		detail.lon->change_hemisphere(convert_hemisphere_lon(detail.lon_hem.value()));

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
