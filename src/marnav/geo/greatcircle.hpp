#ifndef __GEO__GREATCIRCLE__HPP__
#define __GEO__GREATCIRCLE__HPP__

#include "position.hpp"

namespace marnav
{
namespace geo
{

double central_spherical_angle(const position &, const position &);
double distance_sphere(const position &, const position &);
double distance_ellipsoid_vincenty(const position &, const position &, double &, double &);
position point_ellipsoid_vincenty(const position &, double, double, double &);
double distance_ellipsoid_lambert(const position &, const position &);

}}

#endif
