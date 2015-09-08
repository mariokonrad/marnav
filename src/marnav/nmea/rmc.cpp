#include "rmc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
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
	check_value(h, {direction::EAST, direction::WEST}, "mag var hemisphere");
	mag = t;
	mag_hem = h;
}

std::unique_ptr<sentence> rmc::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	// before and after NMEA 2.3
	if ((fields.size() < 11) || (fields.size() > 12))
		throw std::invalid_argument{"invalid number of fields in rmc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rmc>();
	result->set_talker(talker);
	rmc & detail = static_cast<rmc &>(*result);

	read(fields[0], detail.time_utc);
	read(fields[1], detail.status);
	read(fields[2], detail.lat);
	read(fields[3], detail.lat_hem);
	read(fields[4], detail.lon);
	read(fields[5], detail.lon_hem);
	read(fields[6], detail.sog);
	read(fields[7], detail.heading);
	read(fields[8], detail.date);
	read(fields[9], detail.mag);
	read(fields[10], detail.mag_hem);

	// NMEA 2.3 or newer
	if (fields.size() > 11)
		read(fields[11], detail.mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	if (detail.lat && detail.lat_hem)
		detail.lat->change_hemisphere(convert_hemisphere_lat(detail.lat_hem.value()));
	if (detail.lon && detail.lon_hem)
		detail.lon->change_hemisphere(convert_hemisphere_lon(detail.lon_hem.value()));

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
