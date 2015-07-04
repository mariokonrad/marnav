#include "gll.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * gll::TAG;

gll::gll()
	: sentence(ID, TAG, talker_id::global_positioning_system)
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

std::unique_ptr<sentence> gll::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in gll::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gll>();
	result->set_talker(talker);
	gll & detail = static_cast<gll &>(*result);

	read(fields[0], detail.lat);
	read(fields[1], detail.lat_hem);
	read(fields[2], detail.lon);
	read(fields[3], detail.lon_hem);
	read(fields[4], detail.time_utc);
	read(fields[5], detail.status);

	return result;
}

std::vector<std::string> gll::get_data() const
{
	return {to_string(lat), to_string(lat_hem), to_string(lon), to_string(lon_hem),
		to_string(time_utc), to_string(status)};
}
}
}
