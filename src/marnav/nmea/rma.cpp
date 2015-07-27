#include "rma.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
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

void rma::set_magnetic_var(double t, direction h) throw(std::invalid_argument)
{
	check_value(h, {direction::EAST, direction::WEST}, "mag var hemisphere");
	magnetic_var = t;
	magnetic_var_hem = h;
}

std::unique_ptr<sentence> rma::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 11)
		throw std::invalid_argument{"invalid number of fields in rma::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rma>();
	result->set_talker(talker);
	rma & detail = static_cast<rma &>(*result);

	read(fields[0], detail.blink_warning);
	read(fields[1], detail.lat);
	read(fields[2], detail.lat_hem);
	read(fields[3], detail.lon);
	read(fields[4], detail.lon_hem);
	read(fields[5], detail.time_diff_a);
	read(fields[6], detail.time_diff_b);
	read(fields[7], detail.sog);
	read(fields[8], detail.track);
	read(fields[9], detail.magnetic_var);
	read(fields[10], detail.magnetic_var_hem);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	if (detail.lat && detail.lat_hem)
		detail.lat->correct_hemisphere(convert_hemisphere_lat(detail.lat_hem.value()));
	if (detail.lon && detail.lon_hem)
		detail.lon->correct_hemisphere(convert_hemisphere_lon(detail.lon_hem.value()));

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

