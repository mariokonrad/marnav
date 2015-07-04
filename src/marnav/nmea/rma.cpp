#include "rma.hpp"
#include "io.hpp"
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
	read(fields[9], detail.magnetic_variation);
	read(fields[10], detail.magnetic_variation_hem);

	return result;
}

std::vector<std::string> rma::get_data() const
{
	return {to_string(blink_warning), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(time_diff_a), to_string(time_diff_b), to_string(sog),
		to_string(track), to_string(magnetic_variation), to_string(magnetic_variation_hem)};
}
}
}

