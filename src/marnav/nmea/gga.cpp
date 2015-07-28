#include "gga.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * gga::TAG;

gga::gga()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
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

std::unique_ptr<sentence> gga::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 14)
		throw std::invalid_argument{"invalid number of fields in gga::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gga>();
	result->set_talker(talker);
	gga & detail = static_cast<gga &>(*result);

	read(fields[0], detail.time);
	read(fields[1], detail.lat);
	read(fields[2], detail.lat_hem);
	read(fields[3], detail.lon);
	read(fields[4], detail.lon_hem);
	read(fields[5], detail.quality_indicator);
	read(fields[6], detail.n_satellites);
	read(fields[7], detail.hor_dilution);
	read(fields[8], detail.altitude);
	read(fields[9], detail.altitude_unit);
	read(fields[10], detail.geodial_separation);
	read(fields[11], detail.geodial_separation_unit);
	read(fields[12], detail.dgps_age);
	read(fields[13], detail.dgps_ref);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	if (detail.lat && detail.lat_hem)
		detail.lat->correct_hemisphere(convert_hemisphere_lat(detail.lat_hem.value()));
	if (detail.lon && detail.lon_hem)
		detail.lon->correct_hemisphere(convert_hemisphere_lon(detail.lon_hem.value()));

	return result;
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
