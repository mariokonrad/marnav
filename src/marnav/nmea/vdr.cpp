#include "vdr.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vdr::TAG;

vdr::vdr()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

vdr::vdr(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vdr"};

	read(*(first + 0), degrees_true);
	read(*(first + 1), degrees_true_ref);
	read(*(first + 2), degrees_mag);
	read(*(first + 3), degrees_mag_ref);
	read(*(first + 4), speed);
	read(*(first + 5), speed_unit);
}

void vdr::set_degrees_true(double t) noexcept
{
	degrees_true = t;
	degrees_true_ref = reference::TRUE;
}

void vdr::set_degrees_mag(double t) noexcept
{
	degrees_mag = t;
	degrees_mag_ref = reference::MAGNETIC;
}

void vdr::set_speed(double t) noexcept
{
	speed = t;
	speed_unit = unit::velocity::knot;
}

std::unique_ptr<sentence> vdr::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<vdr>(new vdr(talker, first, last));
}

std::vector<std::string> vdr::get_data() const
{
	return {to_string(degrees_true), to_string(degrees_true_ref), to_string(degrees_mag),
		to_string(degrees_mag_ref), to_string(speed), to_string(speed_unit)};
}
}
}
