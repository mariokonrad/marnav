#include "gga.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>
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

std::unique_ptr<sentence> gga::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 14)
		throw std::invalid_argument{"invalid number of fields in gga::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gga>();
	result->set_talker(talker);
	gga & detail = static_cast<gga &>(*result);

	read(*(first + 0), detail.time);
	read(*(first + 1), detail.lat);
	read(*(first + 2), detail.lat_hem);
	read(*(first + 3), detail.lon);
	read(*(first + 4), detail.lon_hem);
	read(*(first + 5), detail.quality_indicator);
	read(*(first + 6), detail.n_satellites);
	read(*(first + 7), detail.hor_dilution);
	read(*(first + 8), detail.altitude);
	read(*(first + 9), detail.altitude_unit);
	read(*(first + 10), detail.geodial_separation);
	read(*(first + 11), detail.geodial_separation_unit);
	read(*(first + 12), detail.dgps_age);
	read(*(first + 13), detail.dgps_ref);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	detail.lat = correct_hemisphere(detail.lat, detail.lat_hem);
	detail.lon = correct_hemisphere(detail.lon, detail.lon_hem);

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
