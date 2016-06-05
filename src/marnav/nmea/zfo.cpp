#include "zfo.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * zfo::TAG;

zfo::zfo()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

zfo::zfo(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zfo"};

	read(*(first + 0), time_utc);
	read(*(first + 1), time_elapsed);
	read(*(first + 2), waypoint_id);
}

void zfo::set_waypoint_id(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

std::unique_ptr<sentence> zfo::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<zfo>(new zfo(talker, first, last));
}

std::vector<std::string> zfo::get_data() const
{
	return {to_string(time_utc), to_string(time_elapsed), to_string(waypoint_id)};
}
}
}
