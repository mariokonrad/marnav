#include "bww.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * bww::TAG;

bww::bww()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void bww::set_bearing_true(double t) noexcept
{
	bearing_true = t;
	bearing_true_ref = reference::TRUE;
}

void bww::set_bearing_mag(double t) noexcept
{
	bearing_mag = t;
	bearing_mag_ref = reference::MAGNETIC;
}

void bww::set_waypoint_to(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_to = id;
}

void bww::set_waypoint_from(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_from = id;
}

std::unique_ptr<sentence> bww::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in bww::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<bww>();
	result->set_talker(talker);
	bww & detail = static_cast<bww &>(*result);

	read(*(first + 0), detail.bearing_true);
	read(*(first + 1), detail.bearing_true_ref);
	read(*(first + 2), detail.bearing_mag);
	read(*(first + 3), detail.bearing_mag_ref);
	read(*(first + 4), detail.waypoint_to);
	read(*(first + 5), detail.waypoint_from);

	return result;
}

std::vector<std::string> bww::get_data() const
{
	return {to_string(bearing_true), to_string(bearing_true_ref), to_string(bearing_mag),
		to_string(bearing_mag_ref), to_string(waypoint_to), to_string(waypoint_from)};
}
}
}
