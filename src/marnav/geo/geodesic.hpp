#ifndef MARNAV__GEO__GREATCIRCLE__HPP
#define MARNAV__GEO__GREATCIRCLE__HPP

#include <marnav/geo/position.hpp>

namespace marnav
{
namespace geo
{
double central_spherical_angle(const position & start, const position & destination);
double distance_sphere(const position & start, const position & destination);
double distance_ellipsoid_vincenty(
	const position & start, const position & destination, double & alpha1, double & alpha2);
position point_ellipsoid_vincenty(const position &, double, double, double &);
double distance_ellipsoid_lambert(const position & start, const position & destination);
}
}

#endif
