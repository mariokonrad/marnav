#include "rma.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * rma::TAG;

rma::rma()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
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

std::unique_ptr<sentence> rma::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 11)
		throw std::invalid_argument{"invalid number of fields in rma::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rma>();
	result->set_talker(talker);
	rma & detail = static_cast<rma &>(*result);

	read(*(first + 0), detail.blink_warning);
	read(*(first + 1), detail.lat);
	read(*(first + 2), detail.lat_hem);
	read(*(first + 3), detail.lon);
	read(*(first + 4), detail.lon_hem);
	read(*(first + 5), detail.time_diff_a);
	read(*(first + 6), detail.time_diff_b);
	read(*(first + 7), detail.sog);
	read(*(first + 8), detail.track);
	read(*(first + 9), detail.magnetic_var);
	read(*(first + 10), detail.magnetic_var_hem);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	detail.lat = correct_hemisphere(detail.lat, detail.lat_hem);
	detail.lon = correct_hemisphere(detail.lon, detail.lon_hem);

	return result;
}

std::vector<std::string> rma::get_data() const
{
	return {to_string(blink_warning), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(time_diff_a), to_string(time_diff_b), to_string(sog),
		to_string(track), to_string(magnetic_var), to_string(magnetic_var_hem)};
}
}
}
