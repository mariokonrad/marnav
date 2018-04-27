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

vdr::vdr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vdr"};

	read(*(first + 0), degrees_true_);
	read(*(first + 1), degrees_true_ref_);
	read(*(first + 2), degrees_mag_);
	read(*(first + 3), degrees_mag_ref_);
	read(*(first + 4), speed_);
	read(*(first + 5), speed_unit_);
}

void vdr::set_degrees_true(double t) noexcept
{
	degrees_true_ = t;
	degrees_true_ref_ = reference::TRUE_NORTH;
}

void vdr::set_degrees_mag(double t) noexcept
{
	degrees_mag_ = t;
	degrees_mag_ref_ = reference::MAGNETIC;
}

void vdr::set_speed(double t) noexcept
{
	speed_ = t;
	speed_unit_ = unit::velocity::knot;
}

void vdr::append_data_to(std::string & s) const
{
	append(s, to_string(degrees_true_));
	append(s, to_string(degrees_true_ref_));
	append(s, to_string(degrees_mag_));
	append(s, to_string(degrees_mag_ref_));
	append(s, to_string(speed_));
	append(s, to_string(speed_unit_));
}
}
}
