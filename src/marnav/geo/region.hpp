#ifndef MARNAV__GEO__REGION__HPP
#define MARNAV__GEO__REGION__HPP

#include <marnav/geo/position.hpp>

namespace marnav
{
namespace geo
{

/// @brief This class represents a geographical region, defined
/// by two coordinates top/left and bottom/right. The
/// coordinates are a pair of lat/lon.
///
/// This geographical region is not of arbitrary size, nor
/// is it rectangluar. The size and shape of a region is
/// variable, depending on the location and boundaries,
/// specified by latitude and longitude. Towards poles
/// the shape will be more triangluar than in the vincinity
/// of the equator.
///
/// This is not a special handling, it results from the fact
/// that, that the region is defined by two points (p0, p1).
///
/// Example:
/// @code
///       on equator                     near north pole
///
///   p0 (lon=55W)                           p0 (lon=55W)
///    +------------+  (lat=5N)               +--+       (lat=85N)
///    |            |                        :    :
///    |            |                       :      :
///  ================== (eq.)              :        :
///    |            |                     :          :
///    |            |                    :            :
///    +------------+  (lat=5S)         +--------------+ (lat=75N)
///                 p1 (lon=20W)                       p1 (lon=20W)
///
/// @endcode
///
/// It is perfectly possible for a region to overlap the date line,
/// as shown here:
/// @code
///
///           date line (180W == 180E)
///  p0       I
///   +-------I------+
///   |       I      |
///   |       I      |
///   |       I      |
///   |       I      |
///   |       I      |
///   +-------I------+
///           I      p1
///
/// @endcode
///
class region
{
public:
	region() = delete;
	region(const position & a0, const position & a1);
	region(const position & a, double d_lat, double d_lon);

	region(const region &) = default;
	region(region &&) noexcept = default;

	region & operator=(const region &) = default;
	region & operator=(region &&) noexcept = default;

	longitude left() const;
	longitude right() const;
	latitude top() const;
	latitude bottom() const;

	bool inside(const position & p) const;

private:
	position p0_; // top, left
	position p1_; // bottom, right
};
}
}

#endif
