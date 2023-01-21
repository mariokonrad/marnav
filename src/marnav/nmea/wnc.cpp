#include <marnav/nmea/wnc.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav::nmea
{
constexpr sentence_id wnc::ID;
constexpr const char * wnc::TAG;

wnc::wnc()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

wnc::wnc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in wnc"};

	std::optional<unit::distance> distance_nm_unit;
	std::optional<unit::distance> distance_km_unit;

	read(*(first + 0), distance_nm_);
	read(*(first + 1), distance_nm_unit);
	read(*(first + 2), distance_km_);
	read(*(first + 3), distance_km_unit);
	read(*(first + 4), waypoint_to_);
	read(*(first + 5), waypoint_from_);

	check_value(distance_nm_unit, {unit::distance::nm}, "distance nm unit");
	check_value(distance_km_unit, {unit::distance::km}, "distance km unit");
}

void wnc::set_distance_nm(units::length t) noexcept
{
	distance_nm_ = t.get<units::nautical_miles>();
}

void wnc::set_distance_km(units::length t) noexcept
{
	distance_km_ = t.get<units::kilometers>();
}

std::optional<units::length> wnc::get_distance_nm() const
{
	if (!distance_nm_)
		return {};
	return {*distance_nm_};
}

std::optional<units::length> wnc::get_distance_km() const
{
	if (!distance_km_)
		return {};
	return {*distance_km_};
}

void wnc::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(distance_nm_));
	append(s, to_string_if(unit::distance::nm, distance_nm_));
	append(s, to_string(distance_km_));
	append(s, to_string_if(unit::distance::km, distance_km_));
	append(s, to_string(waypoint_to_));
	append(s, to_string(waypoint_from_));
}
}
