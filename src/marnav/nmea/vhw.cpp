#include "vhw.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * vhw::TAG;

vhw::vhw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
	, degrees_true_(reference::TRUE)
{
}

vhw::vhw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in vhw"};

	read(*(first + 0), heading_empty_);
	read(*(first + 1), degrees_true_);
	read(*(first + 2), heading_);
	read(*(first + 3), degrees_mag_);
	read(*(first + 4), speed_knots_);
	read(*(first + 5), speed_knots_unit_);
	read(*(first + 6), speed_kmh_);
	read(*(first + 7), speed_kmh_unit_);
}

void vhw::set_heading(double t) noexcept
{
	heading_ = t;
	degrees_mag_ = reference::MAGNETIC;
}

void vhw::set_speed_knots(double t) noexcept
{
	speed_knots_ = t;
	speed_knots_unit_ = unit::velocity::knot;
}

void vhw::set_speed_kmh(double t) noexcept
{
	speed_kmh_ = t;
	speed_kmh_unit_ = unit::velocity::kmh;
}

void vhw::append_data_to(std::string & s) const
{
	append(s, to_string(heading_empty_));
	append(s, to_string(degrees_true_));
	append(s, to_string(heading_));
	append(s, to_string(degrees_mag_));
	append(s, to_string(speed_knots_));
	append(s, to_string(speed_knots_unit_));
	append(s, to_string(speed_kmh_));
	append(s, to_string(speed_kmh_unit_));
}
}
}
