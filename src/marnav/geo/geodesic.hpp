#ifndef MARNAV__GEO__GREATCIRCLE__HPP
#define MARNAV__GEO__GREATCIRCLE__HPP

#include <marnav/geo/position.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace geo
{
MARNAV_EXPORT double central_spherical_angle(const position & start, const position & destination);
MARNAV_EXPORT double distance_sphere(const position & start, const position & destination);
MARNAV_EXPORT double distance_ellipsoid_vincenty(
	const position & start, const position & destination, double & alpha1, double & alpha2);
MARNAV_EXPORT position point_ellipsoid_vincenty(const position &, double, double, double &);
MARNAV_EXPORT double distance_ellipsoid_lambert(const position & start, const position & destination);
}
}

#endif
