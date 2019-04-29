#include "geodesic.hpp"
#include <cmath>

namespace marnav
{
namespace geo
{

/// This geodesic functions may not be the best possible, but they are
/// sufficient for their purpose.

namespace
{
/// mean radius
static constexpr const double earth_radius = 6378000.0; // [m]

/// semi-major axis according to WGS84
static constexpr const double earth_semi_major_axis = 6378137.0; // [m]

/// flattening according to WGS84
static constexpr const double earth_flattening = 1.0 / 298.257223563;

/// Computes the square of the specified value.
template <typename T> static T sqr(const T & a)
{
	return a * a;
}

/// Returns the spherical angle between the two specified position in rad.
///
/// @param[in] p0_lat Latitude in rad of start point.
/// @param[in] p0_lon Longitude in rad of start point.
/// @param[in] p1_lat Latitude in rad of destination point.
/// @param[in] p1_lon Longitude in rad of destination point.
/// @return Spherical angle inbetweenn in rad.
static double central_spherical_angle_rad(
	double p0_lat, double p0_lon, double p1_lat, double p1_lon)
{
	// not used because of potential numerical problems:
	// return acos(sin(p1_lat) * sin(p0_lat) + cos(p1_lat) * cos(p0_lat) * cos(p1_lon -
	// p0_lon));

	return atan(
		sqrt(sqr(cos(p1_lat) * sin(p1_lon - p0_lon))
			+ sqr(cos(p0_lat) * sin(p1_lat) - sin(p0_lat) * cos(p1_lat) * cos(p1_lon - p0_lon)))
		/ (sin(p0_lat) * sin(p1_lat) + cos(p0_lat) * cos(p1_lat) * cos(p1_lon - p0_lon)));
}
}

/// Returns the spherical angle between the two specified position in rad.
///
/// @param[in] start Start point.
/// @param[in] destination Destination point.
/// @return Spherical angle inbetweenn in rad.
double central_spherical_angle(const position & start, const position & destination)
{
	const auto p0 = deg2rad(start);
	const auto p1 = deg2rad(destination);
	return central_spherical_angle_rad(p0.lat(), p0.lon(), p1.lat(), p1.lon());
}

/// Calculates distance of two points on earth, approximated as sphere.
///
/// @param[in] start Start point.
/// @param[in] destination Destination point.
/// @return The distance in meters.
double distance_sphere(const position & start, const position & destination)
{
	return earth_radius * central_spherical_angle(start, destination);
}

/// Calculates the distance on an ellipsoid between start and destination points.
///
/// (indirect problem)
///
/// This uses the method of Vincenty (see inverse.pdf, inverse formulae,
/// http://en.wikipedia.org/wiki/Vincenty%27s_formulae)
///
/// @param[in] start Start point.
/// @param[in] destination Destination point.
/// @param[out] alpha1 Azimuth
/// @param[out] alpha2 Reverse Azimuth
/// @return Distance in meters. NAN if formula failed to converge.
double distance_ellipsoid_vincenty(
	const position & start, const position & destination, double & alpha1, double & alpha2)
{
	if (start == destination)
		return 0.0;

	const position p0 = deg2rad(start);
	const position p1 = deg2rad(destination);

	const double f = earth_flattening;
	const double a = earth_semi_major_axis;
	const double b = (1.0 - f) * a;

	const double L = p1.lon() - p0.lon();
	const double U1 = atan((1.0 - f) * tan(p0.lat()));
	const double U2 = atan((1.0 - f) * tan(p1.lat()));

	double lambda = L; // first approximation

	const double sin_U1 = sin(U1);
	const double sin_U2 = sin(U2);
	const double cos_U1 = cos(U1);
	const double cos_U2 = cos(U2);

	double sigma = 0.0;
	double sin_sigma = sin(sigma);
	double cos_sigma = cos(sigma);
	double cos_sqr_alpha = 0.0;
	double cos_2_sigma_m = 0.0;
	double sin_lambda = sin(lambda);
	double cos_lambda = cos(lambda);

	double d_lambda = 0.0;

	int iteration = 200;
	do {
		sin_lambda = sin(lambda);
		cos_lambda = cos(lambda);

		sin_sigma = sqrt(sqr(cos_U2 * sin_lambda)
			+ sqr(cos_U1 * sin_U2 - sin_U1 * cos_U2 * cos_lambda)); // eq 14

		cos_sigma = sin_U1 * sin_U2 + cos_U1 * cos_U2 * cos_lambda; // eq 15

		sigma = atan2(sin_sigma, cos_sigma); // eq 16

		double sin_alpha = cos_U1 * cos_U2 * sin_lambda / sin_sigma; // eq 17

		cos_sqr_alpha = 1.0 - sqr(sin_alpha); // cos^2(alpha) = 1-sin^2(alpha)

		cos_2_sigma_m = cos_sigma - 2.0 * sin_U1 * sin_U2 / cos_sqr_alpha; // eq 18
		if (std::isnan(cos_2_sigma_m))
			cos_2_sigma_m = 0.0; // equatorial line

		double C = f / 16.0 * cos_sqr_alpha * (4.0 + f * (4.0 - 3.0 * cos_sqr_alpha)); // eq 10

		double old_lambda = lambda; // save current lambda to calc delta lambda
		lambda = L
			+ (1.0 - C) * f * sin_alpha
				* (sigma
					  + C * sin_sigma
						  * (cos_2_sigma_m
								+ C * cos_sigma * (-1.0 + 2.0 * sqr(cos_2_sigma_m)))); // eq 11

		d_lambda = std::abs(old_lambda - lambda);
	} while ((--iteration > 0) && (d_lambda > 1.0e-12));

	if (iteration <= 0)
		return NAN;

	double u_sqr = cos_sqr_alpha * (sqr(a) - sqr(b)) / sqr(b);
	double A = 1.0
		+ u_sqr / 16384.0
			* (4096.0 + u_sqr * (-768.0 + u_sqr * (320.0 - 175.0 * u_sqr))); // eq 3
	double B
		= u_sqr / 1024.0 * (256.0 + u_sqr * (-128.0 + u_sqr * (74.0 - 47.0 * u_sqr))); // eq 4
	double d_sigma = B * sin_sigma
		* (cos_2_sigma_m + B / 4.0 * (cos_sigma * (-1.0 + 2.0 * sqr(cos_2_sigma_m)))
			  - B / 6.0 * cos_2_sigma_m * (-3.0 + 4.0 * sqr(sin_sigma))
				  * (-3.0 + 4.0 * sqr(cos_2_sigma_m))); // eq 6
	double s = A * b * (sigma - d_sigma); // eq 19

	alpha1 = atan2(cos_U2 * sin_lambda, cos_U1 * sin_U2 - sin_U1 * cos_U2 * cos_lambda);
	alpha2 = atan2(cos_U1 * sin_lambda, -sin_U1 * cos_U2 + cos_U1 * sin_U2 * cos_lambda);

	return s;
}

/// Calculates a position from a starting point in a direction and of a certain distance.
///
/// (direct problem)
///
/// This uses the method of Vincenty (see inverse.pdf, direct formulae,
/// http://en.wikipedia.org/wiki/Vincenty%27s_formulae)
///
/// @param[in] start Starting point.
/// @param[in] s Distance in meters.
/// @param[in] alpha1 Azimuth in rad.
/// @param[out] alpha2
/// @return The point at the specified distance.
position point_ellipsoid_vincenty(
	const position & start, double s, double alpha1, double & alpha2)
{
	if (std::abs(s) < 1.0e-4)
		return start;

	const position p0 = deg2rad(start);

	const double f = earth_flattening;
	const double a = earth_semi_major_axis;
	const double b = (1.0 - f) * a;

	const double sin_alpha1 = sin(alpha1);
	const double cos_alpha1 = cos(alpha1);

	const double tan_U1 = (1.0 - f) * tan(p0.lat());
	const double U1 = atan(tan_U1);

	const double sin_U1 = sin(U1);
	const double cos_U1 = cos(U1);

	const double sigma1 = atan2(tan_U1, cos_alpha1);

	const double sin_alpha = cos(U1) * sin_alpha1;
	const double sin_sqr_alpha = sqr(sin_alpha);

	const double cos_sqr_alpha = (1.0 - sin_alpha) * (1.0 + sin_alpha);

	const double u_sqr = cos_sqr_alpha * (sqr(a) - sqr(b)) / sqr(b);

	const double A = 1.0
		+ u_sqr / 16384.0
			* (4096.0 + u_sqr * (-768.0 + u_sqr * (320.0 - 175.0 * u_sqr))); // eq 3

	const double B
		= u_sqr / 1024.0 * (256.0 + u_sqr * (-128.0 + u_sqr * (74.0 - 47.0 * u_sqr))); // eq 4

	double sigma_0 = s / (b * A);
	double sigma = sigma_0;

	double d_sigma = std::abs(sigma);

	double sin_sigma = 0.0;
	double cos_sigma = 0.0;
	double cos_2_sigma_m = 0.0;
	double cos_sqr_2_sigma_m = 0.0;
	double lambda = 0.0;
	double C = 0.0;
	double L = 0.0;

	do {
		cos_2_sigma_m = cos(2.0 * sigma1 + sigma);
		cos_sqr_2_sigma_m = sqr(cos_2_sigma_m);
		cos_sigma = cos(sigma);
		sin_sigma = sin(sigma);
		double delta_sigma = B * sin_sigma
			* (cos_2_sigma_m
				  + B / 4.0 * (cos_sigma * (-1.0 + 2.0 * cos_sqr_2_sigma_m)
								  - B / 6.0 * cos_2_sigma_m * (-3.0 + 4.0 * sqr(sin_sigma))
									  * (-3.0 + 4.0 * cos_sqr_2_sigma_m)));

		double old_sigma = sigma;
		sigma = sigma_0 + delta_sigma;
		d_sigma = std::abs(old_sigma - sigma);
	} while (d_sigma > 1.0e-12);

	latitude lat = atan2(sin_U1 * cos_sigma + cos_U1 * sin_sigma * cos_alpha1, (1.0 - f)
			* sqrt(sin_sqr_alpha + sqr(sin_U1 * sin_sigma - cos_U1 * cos_sigma * cos_alpha1)));
	C = (f / 16.0) * cos_sqr_alpha * (4.0 + f * (4.0 - 3.0 * cos_sqr_alpha));
	lambda
		= atan2(sin_sigma * sin_alpha1, cos_U1 * cos_sigma - sin_U1 * sin_sigma * cos_alpha1);
	L = lambda
		- (1.0 - C) * f * sin_alpha
			* (sigma
				  + C * sin_sigma
					  * (cos_2_sigma_m + C * cos_sigma * (-1.0 + 2.0 * cos_sqr_2_sigma_m)));
	longitude lon = p0.lon() + L;
	alpha2 = atan2(sin_alpha, -sin_U1 * sin_sigma + cos_U1 * cos_sigma * cos_alpha1);

	return rad2deg(position{lat, lon});
}

/// Calculates the distance on an ellipsoid between start and destination points.
///
/// This uses the method of Lambert.
///
/// @param[in] start Start point.
/// @param[in] destination Destination point.
/// @return Distance in meters.
double distance_ellipsoid_lambert(const position & start, const position & destination)
{
	const position p0 = deg2rad(start);
	const position p1 = deg2rad(destination);

	const double r = 1.0 / earth_flattening;

	const double t1_lat = atan((r - 1.0) / r) * tan(p0.lat());
	const double t1_lon = p0.lon();
	const double t2_lat = atan((r - 1.0) / r) * tan(p1.lat());
	const double t2_lon = p1.lon();

	const double sigma = central_spherical_angle_rad(t1_lat, t1_lon, t2_lat, t2_lon);
	const double P = (t1_lat + t2_lat) / 2.0;
	const double Q = (t2_lat - t1_lat) / 2.0;
	const double X = (sigma - sin(sigma)) * (sqr(sin(P)) * sqr(cos(Q))) / sqr(cos(sigma / 2.0));
	const double Y = (sigma + sin(sigma)) * (sqr(cos(P)) * sqr(sin(Q))) / sqr(sin(sigma / 2.0));

	return earth_radius * (sigma - (X + Y) / (2.0 * r));
}
}
}
