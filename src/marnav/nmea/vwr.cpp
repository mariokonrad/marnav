#include "vwr.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(vwr)

constexpr const char * vwr::TAG;

vwr::vwr()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

vwr::vwr(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in vwr"};

	read(*(first + 0), angle);
	read(*(first + 1), angle_side);
	read(*(first + 2), speed_knots);
	read(*(first + 3), speed_knots_unit);
	read(*(first + 4), speed_mps);
	read(*(first + 5), speed_mps_unit);
	read(*(first + 6), speed_kmh);
	read(*(first + 7), speed_kmh_unit);
}

void vwr::set_angle(double angle, side s) noexcept
{
	this->angle = angle;
	this->angle_side = s;
}

void vwr::set_speed_knots(double t) noexcept
{
	speed_knots = t;
	speed_knots_unit = unit::velocity::knot;
}

void vwr::set_speed_mps(double t) noexcept
{
	speed_mps = t;
	speed_mps_unit = unit::velocity::mps;
}

void vwr::set_speed_kmh(double t) noexcept
{
	speed_kmh = t;
	speed_kmh_unit = unit::velocity::kmh;
}

std::vector<std::string> vwr::get_data() const
{
	return {to_string(angle), to_string(angle_side), to_string(speed_knots),
		to_string(speed_knots_unit), to_string(speed_mps), to_string(speed_mps_unit),
		to_string(speed_kmh), to_string(speed_kmh_unit)};
}
}
}
