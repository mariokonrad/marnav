#include <marnav/nmea/vwr.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id vwr::ID;
constexpr const char * vwr::TAG;

vwr::vwr()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

vwr::vwr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in vwr"};

	read(*(first + 0), angle_);
	read(*(first + 1), angle_side_);
	read(*(first + 2), speed_knots_);
	read(*(first + 3), speed_knots_unit_);
	read(*(first + 4), speed_mps_);
	read(*(first + 5), speed_mps_unit_);
	read(*(first + 6), speed_kmh_);
	read(*(first + 7), speed_kmh_unit_);
}

void vwr::set_angle(double angle, side s) noexcept
{
	angle_ = angle;
	angle_side_ = s;
}

void vwr::set_speed_knots(double t) noexcept
{
	speed_knots_ = t;
	speed_knots_unit_ = unit::velocity::knot;
}

void vwr::set_speed_mps(double t) noexcept
{
	speed_mps_ = t;
	speed_mps_unit_ = unit::velocity::mps;
}

void vwr::set_speed_kmh(double t) noexcept
{
	speed_kmh_ = t;
	speed_kmh_unit_ = unit::velocity::kmh;
}

void vwr::append_data_to(std::string & s) const
{
	append(s, to_string(angle_));
	append(s, to_string(angle_side_));
	append(s, to_string(speed_knots_));
	append(s, to_string(speed_knots_unit_));
	append(s, to_string(speed_mps_));
	append(s, to_string(speed_mps_unit_));
	append(s, to_string(speed_kmh_));
	append(s, to_string(speed_kmh_unit_));
}
}
}
