#ifndef MARNAV_GEO_GREATCIRCLE_HPP
#define MARNAV_GEO_GREATCIRCLE_HPP

#include <marnav/geo/position.hpp>

namespace marnav
{
namespace geo
{
struct distance_result {
	double distance = 0.0; // [m]
	double azimuth = 0.0; // [rad]
	double reverse_azimuth = 0.0; // [rad]

	distance_result() = default;

	explicit distance_result(double dist)
		: distance(dist)
	{
	}

	distance_result(double d, double a, double ra)
		: distance(d)
		, azimuth(a)
		, reverse_azimuth(ra)
	{
	}
};

double central_spherical_angle(const position & start, const position & destination);

distance_result distance_sphere(const position & start, const position & destination);

distance_result distance_ellipsoid_vincenty(
	const position & start, const position & destination);

position point_ellipsoid_vincenty(const position &, double s, double alpha1, double & alpha2);

distance_result distance_ellipsoid_lambert(
	const position & start, const position & destination);
}
}

#endif
