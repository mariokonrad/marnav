#include "gll.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * gll::TAG;

gll::gll()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, mode_indicator(positioning_system_mode_indicator::invalid)
{
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

std::unique_ptr<sentence> gll::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	// older version has no 'mode_indicator'
	const auto size = std::distance(first, last);
	if ((size < 6) || (size > 7))
		throw std::invalid_argument{
			std::string{"invalid number of fields in gll::parse: expected 6, got "}
			+ std::to_string(size)};

	std::unique_ptr<sentence> result = utils::make_unique<gll>();
	result->set_talker(talker);
	gll & detail = static_cast<gll &>(*result);

	read(*(first + 0), detail.lat);
	read(*(first + 1), detail.lat_hem);
	read(*(first + 2), detail.lon);
	read(*(first + 3), detail.lon_hem);
	read(*(first + 4), detail.time_utc);
	read(*(first + 5), detail.data_valid);

	if (size > 6)
		read(*(first + 6), detail.mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	detail.lat = correct_hemisphere(detail.lat, detail.lat_hem);
	detail.lon = correct_hemisphere(detail.lon, detail.lon_hem);

	return result;
}

std::vector<std::string> gll::get_data() const
{
	return {to_string(lat), to_string(lat_hem), to_string(lon), to_string(lon_hem),
		to_string(time_utc), to_string(data_valid), to_string(mode_indicator)};
}
}
}
