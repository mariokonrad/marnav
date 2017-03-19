#include "vhw.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * vhw::TAG;

vhw::vhw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
	, degrees_true(reference::TRUE)
{
}

vhw::vhw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in vhw"};

	read(*(first + 0), heading_empty);
	read(*(first + 1), degrees_true);
	read(*(first + 2), heading);
	read(*(first + 3), degrees_mag);
	read(*(first + 4), speed_knots);
	read(*(first + 5), speed_knots_unit);
	read(*(first + 6), speed_kmh);
	read(*(first + 7), speed_kmh_unit);
}

void vhw::set_heading(double t) noexcept
{
	heading = t;
	degrees_mag = reference::MAGNETIC;
}

void vhw::set_speed_knots(double t) noexcept
{
	speed_knots = t;
	speed_knots_unit = unit::velocity::knot;
}

void vhw::set_speed_kmh(double t) noexcept
{
	speed_kmh = t;
	speed_kmh_unit = unit::velocity::kmh;
}

void vhw::append_data_to(std::string & s) const
{
	append(s, to_string(heading_empty));
	append(s, to_string(degrees_true));
	append(s, to_string(heading));
	append(s, to_string(degrees_mag));
	append(s, to_string(speed_knots));
	append(s, to_string(speed_knots_unit));
	append(s, to_string(speed_kmh));
	append(s, to_string(speed_kmh_unit));
}
}
}
