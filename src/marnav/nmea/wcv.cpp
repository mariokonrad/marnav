#include "wcv.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * wcv::TAG;

wcv::wcv()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
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
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in wcv::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<wcv>();
	result->set_talker(talker);
	wcv & detail = static_cast<wcv &>(*result);

	read(*(first + 0), detail.speed);
	read(*(first + 1), detail.speed_unit);
	read(*(first + 2), detail.waypoint_id);

	return result;
}

std::vector<std::string> wcv::get_data() const
{
	return {format(speed, 1), to_string(speed_unit), to_string(waypoint_id)};
}
}
}
