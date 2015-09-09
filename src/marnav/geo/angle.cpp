#include "angle.hpp"
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <marnav/math/floatingpoint.hpp>

namespace marnav
{
namespace geo
{
angle::angle() noexcept : value(0.0) {}

/// Initializes the angle with the specified angle in degrees.
angle::angle(double deg)
	: value(deg)
{
}

/// Returns the degrees of this angle. This value is always positive.
uint32_t angle::degrees() const noexcept
{
	auto a = std::abs(get());
	a = floor(a);
	return static_cast<uint32_t>(a);
}

/// Returns the minutes of this angle. This value is always positive
/// and is between 0 and 59.
uint32_t angle::minutes() const noexcept
{
	auto a = std::abs(get());
	a -= floor(a);
	a *= 60.0;
	a += epsilon;
	return static_cast<uint32_t>(a);
}

/// Returns the seconds of this angle.
double angle::seconds() const noexcept
{
	auto a = std::abs(get());
	a -= floor(a);
	a *= 60.0;
	a += epsilon;
	a -= floor(a);
	a *= 60.0;
	return a;
}

/// Converts an angle to double, units: degrees.
angle::operator double() const noexcept { return value; }

double angle::get() const noexcept { return value; }

/// Sets the angle in degrees.
void angle::set(double t) noexcept { value = t; }

bool operator==(const angle & a, const angle & b) noexcept
{
	return (&a == &b) || math::is_same(a.value, b.value);
}

void swap(angle & a, angle & b)
{
	std::swap(a.value, b.value);
}

bool operator!=(const angle & a, const angle & b) noexcept { return !(a == b); }

latitude::latitude() noexcept : latitude(0.0) {}

/// Constructs a latitude with the specified angle in degrees.
latitude::latitude(double deg)
	: angle(deg)
{
	check(get());
}

latitude::latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere h)
	: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
				+ static_cast<double>(s) / 3600.0)
		  * ((h == hemisphere::SOUTH) ? -1.0 : 1.0))
{
	check(get());
}

/// Returns the corresponding hemisphere.
latitude::hemisphere latitude::hem() const noexcept
{
	return get() >= 0.0 ? hemisphere::NORTH : hemisphere::SOUTH;
}

bool operator==(const latitude & a, const latitude & b) noexcept
{
	return (&a == &b) || math::is_same(a.get(), b.get());
}

bool operator!=(const latitude & a, const latitude & b) noexcept { return !(a == b); }

/// Corrects the stored value according to the specified hemisphere.
/// This is useful if the stored value was set preliminary, and the
/// hemisphere was nown later.
void latitude::change_hemisphere(hemisphere h)
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

void latitude::check(double a)
{
	if ((a < -90.0) || (a > 90.0))
		throw std::invalid_argument{"invalid value for nmea::latitude"};
}

longitude::longitude() noexcept : longitude(0.0) {}

/// Constructs a longitude with the specified angle in degrees.
longitude::longitude(double deg)
	: angle(deg)
{
	check(get());
}

longitude::longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere h)
	: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
				+ static_cast<double>(s) / 3600.0)
		  * ((h == hemisphere::EAST) ? +1.0 : -1.0))
{
	check(get());
}

/// Returns the corresponding hemisphere.
longitude::hemisphere longitude::hem() const noexcept
{
	return get() < 0.0 ? hemisphere::WEST : hemisphere::EAST;
}

bool operator==(const longitude & a, const longitude & b) noexcept
{
	return (&a == &b) || math::is_same(a.get(), b.get());
}

bool operator!=(const longitude & a, const longitude & b) noexcept { return !(a == b); }

/// Corrects the stored value according to the specified hemisphere.
/// This is useful if the stored value was set preliminary, and the
/// hemisphere was nown later.
void longitude::change_hemisphere(hemisphere h)
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

void longitude::check(double a)
{
	if ((a < -180.0) || (a > 180.0))
		throw std::invalid_argument{"invalid value for nmea::longitude"};
}
}
}
