#include "vbw.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * vbw::TAG;

vbw::vbw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

vbw::vbw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vbw"};

	read(*(first + 0), water_speed_longitudinal_);
	read(*(first + 1), water_speed_transveral_);
	read(*(first + 2), water_speed_status_);
	read(*(first + 3), ground_speed_longitudinal_);
	read(*(first + 4), ground_speed_transveral_);
	read(*(first + 5), water_speed_status_);
}

void vbw::set_water_speed(double l, double t, status s) noexcept
{
	water_speed_longitudinal_ = l;
	water_speed_transveral_ = t;
	water_speed_status_ = s;
}

void vbw::set_ground_speed(double l, double t, status s) noexcept
{
	ground_speed_longitudinal_ = l;
	ground_speed_transveral_ = t;
	ground_speed_status_ = s;
}

void vbw::append_data_to(std::string & s) const
{
	append(s, format(water_speed_longitudinal_, 1));
	append(s, format(water_speed_transveral_, 1));
	append(s, to_string(water_speed_status_));
	append(s, format(ground_speed_longitudinal_, 1));
	append(s, format(ground_speed_transveral_, 1));
	append(s, to_string(ground_speed_status_));
}
}
}
