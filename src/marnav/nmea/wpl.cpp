#include "wpl.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * wpl::TAG;

wpl::wpl()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void wpl::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void wpl::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void wpl::set_waypoint(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

std::unique_ptr<sentence> wpl::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in wpl::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<wpl>();
	result->set_talker(talker);
	wpl & detail = static_cast<wpl &>(*result);

	read(*(first + 0), detail.lat);
	read(*(first + 1), detail.lat_hem);
	read(*(first + 2), detail.lon);
	read(*(first + 3), detail.lon_hem);
	read(*(first + 4), detail.waypoint_id);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	detail.lat = correct_hemisphere(detail.lat, detail.lat_hem);
	detail.lon = correct_hemisphere(detail.lon, detail.lon_hem);

	return result;
}

std::vector<std::string> wpl::get_data() const
{
	return {to_string(lat), to_string(lat_hem), to_string(lon), to_string(lon_hem),
		to_string(waypoint_id)};
}
}
}
