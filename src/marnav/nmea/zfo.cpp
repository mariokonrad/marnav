#include "zfo.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * zfo::TAG;

zfo::zfo()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void zfo::set_waypoint_id(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

std::unique_ptr<sentence> zfo::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zfo::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<zfo>();
	result->set_talker(talker);
	zfo & detail = static_cast<zfo &>(*result);

	read(*(first + 0), detail.time_utc);
	read(*(first + 1), detail.time_elapsed);
	read(*(first + 2), detail.waypoint_id);

	return result;
}

std::vector<std::string> zfo::get_data() const
{
	return {to_string(time_utc), to_string(time_elapsed), to_string(waypoint_id)};
}
}
}
