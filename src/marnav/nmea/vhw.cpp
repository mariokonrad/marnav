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

std::vector<std::string> vhw::get_data() const
{
	return {to_string(heading_empty), to_string(degrees_true), to_string(heading),
		to_string(degrees_mag), to_string(speed_knots), to_string(speed_knots_unit),
		to_string(speed_kmh), to_string(speed_kmh_unit)};
}
}
}
