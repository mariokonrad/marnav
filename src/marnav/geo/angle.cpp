#include "angle.hpp"
#include <cmath>

namespace marnav
{
namespace geo
{
angle::angle()
	: value(0.0)
{
}

angle::angle(double value)
	: value(value)
{
}

/// Returns the degrees of this angle. This value is always positive.
uint32_t angle::degrees() const
{
	auto a = fabs(get());
	a = floor(a);
	return static_cast<uint32_t>(a);
}

/// Returns the minutes of this angle. This value is always positive
/// and is between 0 and 59.
uint32_t angle::minutes() const
{
	auto a = fabs(get());
	a -= floor(a);
	a *= 60.0;
	a += EPSILON;
	return static_cast<uint32_t>(a);
}

/// Returns the seconds of this angle.
double angle::seconds() const
{
	auto a = fabs(get());
	a -= floor(a);
	a *= 60.0;
	a += EPSILON;
	a -= floor(a);
	a *= 60.0;
	return a;
}

/// Converts an angle to double, units: degrees.
angle::operator double() const { return value; }

double angle::get() const { return value; }

void angle::set(double t) { value = t; }

bool operator==(const angle & a, const angle & b) noexcept
{
	return (&a == &b) || (a.value == b.value);
}

latitude::latitude()
	: latitude(0.0)
{
}

latitude::latitude(double value) throw(std::invalid_argument)
	: angle(value)
{
	check(get());
}

latitude::latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem) throw(
	std::invalid_argument)
	: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
				+ static_cast<double>(s) / 3600.0) * ((hem == hemisphere::SOUTH) ? -1.0 : 1.0))
{
	check(get());
}

/// Returns the corresponding hemisphere.
latitude::hemisphere latitude::hem() const
{
	return get() >= 0.0 ? hemisphere::NORTH : hemisphere::SOUTH;
}

/// Corrects the stored value according to the specified hemisphere.
/// This is useful if the stored value was set preliminary, and the
/// hemisphere was nown later.
void latitude::correct_hemisphere(hemisphere h)
{
	switch (h) {
		case hemisphere::NORTH:
			if (hem() == hemisphere::SOUTH)
				set(-get());
			break;
		case hemisphere::SOUTH:
			if (hem() == hemisphere::NORTH)
				set(-get());
			break;
	}
}

void latitude::check(double a) throw(std::invalid_argument)
{
	if ((a < -90.0) || (a > 90.0))
		throw std::invalid_argument{"invalid value for nmea::latitude"};
}

longitude::longitude()
	: longitude(0.0)
{
}

longitude::longitude(double value) throw(std::invalid_argument)
	: angle(value)
{
	check(get());
}

longitude::longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem) throw(
	std::invalid_argument)
	: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
				+ static_cast<double>(s) / 3600.0) * ((hem == hemisphere::EAST) ? -1.0 : 1.0))
{
	check(get());
}

/// Returns the corresponding hemisphere.
longitude::hemisphere longitude::hem() const
{
	return get() >= 0.0 ? hemisphere::WEST : hemisphere::EAST;
}

/// Corrects the stored value according to the specified hemisphere.
/// This is useful if the stored value was set preliminary, and the
/// hemisphere was nown later.
void longitude::correct_hemisphere(hemisphere h)
{
	switch (h) {
		case hemisphere::EAST:
			if (hem() == hemisphere::WEST)
				set(-get());
			break;
		case hemisphere::WEST:
			if (hem() == hemisphere::EAST)
				set(-get());
			break;
	}
}

void longitude::check(double a) throw(std::invalid_argument)
{
	if ((a < -180.0) || (a > 180.0))
		throw std::invalid_argument{"invalid value for nmea::longitude"};
}
}
}
