#include "bwc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * bwc::TAG;

bwc::bwc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
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
	distance_unit = unit::distance::NM;
}

void bwc::set_waypoint(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

std::unique_ptr<sentence> bwc::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if ((fields.size() != 12) && (fields.size() != 13))
		throw std::invalid_argument{"invalid number of fields in bwc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<bwc>();
	result->set_talker(talker);
	bwc & detail = static_cast<bwc &>(*result);

	read(fields[0], detail.time_utc);
	read(fields[1], detail.lat);
	read(fields[2], detail.lat_hem);
	read(fields[3], detail.lon);
	read(fields[4], detail.lon_hem);
	read(fields[5], detail.bearing_true);
	read(fields[6], detail.bearing_true_ref);
	read(fields[7], detail.bearing_mag);
	read(fields[8], detail.bearing_mag_ref);
	read(fields[9], detail.distance);
	read(fields[10], detail.distance_unit);
	read(fields[11], detail.waypoint_id);

	if (fields.size() == 13)
		read(fields[12], detail.mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	if (detail.lat && detail.lat_hem)
		detail.lat->change_hemisphere(convert_hemisphere_lat(detail.lat_hem.value()));
	if (detail.lon && detail.lon_hem)
		detail.lon->change_hemisphere(convert_hemisphere_lon(detail.lon_hem.value()));

	return result;
}

std::vector<std::string> bwc::get_data() const
{
	return {to_string(time_utc), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(bearing_true), to_string(bearing_true_ref),
		to_string(bearing_mag), to_string(bearing_mag_ref), to_string(distance),
		to_string(distance_unit), to_string(waypoint_id), to_string(mode_indicator)};
}
}
}
