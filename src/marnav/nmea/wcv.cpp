#include "wcv.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * wcv::TAG;

wcv::wcv()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

wcv::wcv(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in wcv"};

	read(*(first + 0), speed);
	read(*(first + 1), speed_unit);
	read(*(first + 2), waypoint_id);
}

void wcv::set_speed(double t) noexcept
{
	speed = t;
	speed_unit = unit::velocity::knot;
}

void wcv::set_waypoint(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

std::unique_ptr<sentence> wcv::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<wcv>(new wcv(talker, first, last));
}

std::vector<std::string> wcv::get_data() const
{
	return {format(speed, 1), to_string(speed_unit), to_string(waypoint_id)};
}
}
}
