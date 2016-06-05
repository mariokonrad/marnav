#include "rma.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(rma)

constexpr const char * rma::TAG;

rma::rma()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

rma::rma(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 11)
		throw std::invalid_argument{"invalid number of fields in rma"};

	read(*(first + 0), blink_warning);
	read(*(first + 1), lat);
	read(*(first + 2), lat_hem);
	read(*(first + 3), lon);
	read(*(first + 4), lon_hem);
	read(*(first + 5), time_diff_a);
	read(*(first + 6), time_diff_b);
	read(*(first + 7), sog);
	read(*(first + 8), track);
	read(*(first + 9), magnetic_var);
	read(*(first + 10), magnetic_var_hem);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

void rma::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void rma::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void rma::set_magnetic_var(double t, direction h)
{
	check_value(h, {direction::east, direction::west}, "mag var hemisphere");
	magnetic_var = t;
	magnetic_var_hem = h;
}

std::vector<std::string> rma::get_data() const
{
	return {to_string(blink_warning), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(time_diff_a), to_string(time_diff_b), to_string(sog),
		to_string(track), to_string(magnetic_var), to_string(magnetic_var_hem)};
}
}
}
