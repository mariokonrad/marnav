#include "tll.hpp"

#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * tll::TAG;

tll::tll()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, target_number(0)
	, lat_hem(direction::NORTH)
	, lon_hem(direction::EAST)
	, target_status('T')
{
}

void tll::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void tll::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void tll::set_target_name(const std::string & t)
{
	check_waypoint_id(t);
	target_name = t;
}

std::unique_ptr<sentence> tll::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 9)
		throw std::invalid_argument{"invalid number of fields in tll::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<tll>();
	result->set_talker(talker);
	tll & detail = static_cast<tll &>(*result);

	read(fields[0], detail.target_number);
	read(fields[1], detail.lat);
	read(fields[2], detail.lat_hem);
	read(fields[3], detail.lon);
	read(fields[4], detail.lon_hem);
	read(fields[5], detail.target_name);
	read(fields[6], detail.time_utc);
	read(fields[7], detail.target_status);
	read(fields[8], detail.reference_target);

	return result;
}

std::vector<std::string> tll::get_data() const
{
	return {format(target_number, 2), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(target_name), to_string(time_utc),
		to_string(target_status), to_string(reference_target)};
}
}
}
