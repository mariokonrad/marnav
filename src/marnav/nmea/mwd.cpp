#include "mwd.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * mwd::TAG;

mwd::mwd()
	: sentence(ID, TAG, talker_id::weather_instruments)
{
}

mwd::mwd(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in mwd"};

	read(*(first + 0), direction_true_);
	read(*(first + 1), direction_true_ref_);
	read(*(first + 2), direction_mag_);
	read(*(first + 3), direction_mag_ref_);
	read(*(first + 4), speed_kn_);
	read(*(first + 5), speed_kn_unit_);
	read(*(first + 6), speed_ms_);
	read(*(first + 7), speed_ms_unit_);
}

void mwd::set_direction_true(double t) noexcept
{
	direction_true_ = t;
	direction_true_ref_ = reference::TRUE;
}

void mwd::set_direction_mag(double t) noexcept
{
	direction_mag_ = t;
	direction_mag_ref_ = reference::MAGNETIC;
}

void mwd::set_speed_knots(double t) noexcept
{
	speed_kn_ = t;
	speed_kn_unit_ = unit::velocity::knot;
}

void mwd::set_speed_mps(double t) noexcept
{
	speed_ms_ = t;
	speed_ms_unit_ = unit::velocity::mps;
}

void mwd::append_data_to(std::string & s) const
{
	append(s, format(direction_true_, 1));
	append(s, to_string(direction_true_ref_));
	append(s, format(direction_mag_, 1));
	append(s, to_string(direction_mag_ref_));
	append(s, format(speed_kn_, 1));
	append(s, to_string(speed_kn_unit_));
	append(s, format(speed_ms_, 1));
	append(s, to_string(speed_ms_unit_));
}
}
}
