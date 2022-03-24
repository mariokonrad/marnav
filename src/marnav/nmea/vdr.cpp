#include <marnav/nmea/vdr.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id vdr::ID;
constexpr const char * vdr::TAG;

vdr::vdr()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

vdr::vdr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vdr"};

	reference degrees_true_ref;
	reference degrees_magn_ref;
	unit::velocity speed_unit;

	read(*(first + 0), degrees_true_);
	read(*(first + 1), degrees_true_ref);
	read(*(first + 2), degrees_magn_);
	read(*(first + 3), degrees_magn_ref);
	read(*(first + 4), speed_);
	read(*(first + 5), speed_unit);

	check_value(speed_unit, {unit::velocity::knot}, "speed unit");
}

void vdr::set_degrees_true(double t) noexcept
{
	degrees_true_ = t;
}

void vdr::set_degrees_magn(double t) noexcept
{
	degrees_magn_ = t;
}

void vdr::set_speed(units::velocity t) noexcept
{
	speed_ = t.get<units::knots>();
}

std::optional<units::velocity> vdr::get_speed() const
{
	if (!speed_)
		return {};
	return {*speed_};
}

void vdr::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(degrees_true_));
	append(s, to_string_if(reference::TRUE, degrees_true_));
	append(s, to_string(degrees_magn_));
	append(s, to_string_if(reference::MAGNETIC, degrees_magn_));
	append(s, to_string(speed_));
	append(s, to_string_if(unit::velocity::knot, speed_));
}
}
}
