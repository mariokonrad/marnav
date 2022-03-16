#ifndef MARNAV_NMEA_MAGNETIC_HPP
#define MARNAV_NMEA_MAGNETIC_HPP

#include <marnav/nmea/constants.hpp>
#include <marnav/math/floatingpoint_ulps.hpp>
#include <stdexcept>

namespace marnav::nmea
{
class magnetic
{
public:
	magnetic() = default;

	magnetic(double angle, direction hemisphere)
		: angle_(angle)
		, hemisphere_(hemisphere)
	{
		if (angle_ < 0.0)
			throw std::invalid_argument{"negativ magnetic angle is invalid"};
		if ((hemisphere_ != direction::west) && (hemisphere_ != direction::east))
			throw std::invalid_argument{"invalid value for hemishphere"};
	}

	magnetic(const magnetic &) = default;
	magnetic & operator=(const magnetic &) = default;

	magnetic(magnetic &&) = default;
	magnetic & operator=(magnetic &&) = default;

	double angle() const { return angle_; }
	direction hemisphere() const { return hemisphere_; }

	friend bool operator==(const magnetic & a, const magnetic & b)
	{
		return (a.hemisphere() == b.hemisphere()) && math::nearly_equal(a.angle(), b.angle());
	}

	friend bool operator!=(const magnetic & a, const magnetic & b) { return !(a == b); }

private:
	double angle_ = 0.0;
	direction hemisphere_ = direction::none;
};
}

#endif
