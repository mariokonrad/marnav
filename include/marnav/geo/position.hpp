#ifndef MARNAV__GEO__POSITION__HPP
#define MARNAV__GEO__POSITION__HPP

#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace geo
{

/// @brief Represents a position, consisting of latitude and longitude.
///
/// Immutable.
///
class position
{
public:
	position() = default;
	position(const position &) = default;
	position(position &&) noexcept = default;
	position(const latitude & la, const longitude & lo);

	position & operator=(const position &) = default;
	position & operator=(position &&) noexcept = default;

	bool operator==(const position & other) const;

	inline const latitude & lat() const { return lat_; }
	inline const longitude & lon() const { return lon_; }

private:
	latitude lat_;
	longitude lon_;
};

position deg2rad(const position & p);
position rad2deg(const position & p);
}
}

#endif
