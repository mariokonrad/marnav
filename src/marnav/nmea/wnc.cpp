#include "wnc.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * wnc::TAG;

wnc::wnc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

wnc::wnc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in wnc"};

	read(*(first + 0), distance_nm_);
	read(*(first + 1), distance_nm_unit_);
	read(*(first + 2), distance_km_);
	read(*(first + 3), distance_km_unit_);
	read(*(first + 4), waypoint_to_);
	read(*(first + 5), waypoint_from_);
}

void wnc::set_distance_nm(double t) noexcept
{
	distance_nm_ = t;
	distance_nm_unit_ = unit::distance::nm;
}

void wnc::set_distance_km(double t) noexcept
{
	distance_km_ = t;
	distance_km_unit_ = unit::distance::km;
}

void wnc::append_data_to(std::string & s) const
{
	append(s, to_string(distance_nm_));
	append(s, to_string(distance_nm_unit_));
	append(s, to_string(distance_km_));
	append(s, to_string(distance_km_unit_));
	append(s, to_string(waypoint_to_));
	append(s, to_string(waypoint_from_));
}
}
}
