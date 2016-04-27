#include "angle.hpp"
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <marnav/math/floatingpoint.hpp>

namespace marnav
{
namespace geo
{
/// Returns the degrees of this angle. This value is always positive.
uint32_t angle::degrees() const noexcept
{
	auto a = std::abs(get());
	a = std::floor(a);
	return static_cast<uint32_t>(a);
}

/// Returns the minutes of this angle. This value is always positive
/// and is between 0 and 59.
uint32_t angle::minutes() const noexcept
{
	auto a = std::abs(get());
	a -= std::floor(a);
	a *= 60.0;
	a += epsilon;
	return static_cast<uint32_t>(a);
}

/// Returns the seconds of this angle.
double angle::seconds() const noexcept
{
	auto a = std::abs(get());
	a -= std::floor(a);
	a *= 60.0;
	a += epsilon;
	a -= std::floor(a);
	a *= 60.0;
	return a;
}

void swap(angle & a, angle & b) noexcept { std::swap(a.value, b.value); }

bool operator==(const angle & a, const angle & b) noexcept
{
	return (&a == &b) || math::is_same(a.value, b.value);
}

bool operator!=(const angle & a, const angle & b) noexcept { return !(a == b); }

/// Constructs a latitude with the specified angle in degrees.
latitude::latitude(double deg)
	: angle(deg)
{
	check(get());
}

/// Initializes the object with the specified angle.
/// Corrects the stored value according to the specified hemisphere.
///
/// @param[in] degrees Angle in degrees.
/// @param[in] h Hemisphere
latitude::latitude(double degrees, hemisphere h)
	: angle(degrees)
{
	check(get());

	switch (h) {
		case hemisphere::north:
			if (hem() == hemisphere::south)
				set(-get());
			break;
		case hemisphere::south:
			if (hem() == hemisphere::north)
				set(-get());
			break;
	}
}

latitude::latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere h)
	: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
				+ static_cast<double>(s) / 3600.0)
		  * ((h == hemisphere::south) ? -1.0 : 1.0))
{
	check(get());
}

bool operator==(const latitude & a, const latitude & b) noexcept
{
	return (&a == &b) || math::is_same(a.get(), b.get());
}

bool operator!=(const latitude & a, const latitude & b) noexcept { return !(a == b); }

void latitude::check(double a)
{
	if ((a < min) || (a > max))
		throw std::invalid_argument{"invalid value for nmea::latitude"};
}

/// Constructs a longitude with the specified angle in degrees.
longitude::longitude(double deg)
	: angle(deg)
{
	check(get());
}

/// Initializes the object with the specified angle.
/// Corrects the stored value according to the specified hemisphere.
///
/// @param[in] degrees Angle in degrees.
/// @param[in] h Hemisphere
longitude::longitude(double degrees, hemisphere h)
	: angle(degrees)
{
	check(get());

	switch (h) {
		case hemisphere::east:
			if (hem() == hemisphere::west)
				set(-get());
			break;
		case hemisphere::west:
			if (hem() == hemisphere::east)
				set(-get());
			break;
	}
}

longitude::longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere h)
	: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
				+ static_cast<double>(s) / 3600.0)
		  * ((h == hemisphere::east) ? +1.0 : -1.0))
{
	check(get());
}

bool operator==(const longitude & a, const longitude & b) noexcept
{
	return (&a == &b) || math::is_same(a.get(), b.get());
}

bool operator!=(const longitude & a, const longitude & b) noexcept { return !(a == b); }

void longitude::check(double a)
{
	if ((a < min) || (a > max))
		throw std::invalid_argument{"invalid value for nmea::longitude"};
}
}
}
