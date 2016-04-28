#include "wnc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * wnc::TAG;

wnc::wnc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void wnc::set_distance_nm(double t) noexcept
{
	distance_nm = t;
	distance_nm_unit = unit::distance::nm;
}

void wnc::set_distance_km(double t) noexcept
{
	distance_km = t;
	distance_km_unit = unit::distance::km;
}

void wnc::set_waypoint_to(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_to = id;
}

void wnc::set_waypoint_from(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_from = id;
}

std::unique_ptr<sentence> wnc::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in wnc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<wnc>();
	result->set_talker(talker);
	wnc & detail = static_cast<wnc &>(*result);

	read(*(first + 0), detail.distance_nm);
	read(*(first + 1), detail.distance_nm_unit);
	read(*(first + 2), detail.distance_km);
	read(*(first + 3), detail.distance_km_unit);
	read(*(first + 4), detail.waypoint_to);
	read(*(first + 5), detail.waypoint_from);

	return result;
}

std::vector<std::string> wnc::get_data() const
{
	return {to_string(distance_nm), to_string(distance_nm_unit), to_string(distance_km),
		to_string(distance_km_unit), to_string(waypoint_to), to_string(waypoint_from)};
}
}
}
