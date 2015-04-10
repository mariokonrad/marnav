#include "greatcircle.hpp"
#include <cmath>

namespace marnav
{
namespace geo
{

static const double EARTH_RADIUS = 6378000.0; // [m] mean radius
static const double EARTH_SEMI_MAJOR_AXIS = 6378137.0; // [m] semi-major axis according to WGS84
static const double EARTH_FLATTENING = 1.0 / 298.257223563; // flattening according to WGS84

template <typename T> static T sqr(const T & a) { return a * a; }

double central_spherical_angle(const position & p0, const position & p1)
{
	// not used because of potential numerical problems:
	// return acos(sin(p1.lat) * sin(p0.lat) + cos(p1.lat) * cos(p0.lat) * cos(p1.lon -
	// p0.lon));

	return atan(
		sqrt(sqr(cos(p1.lat) * sin(p1.lon - p0.lon))
			+ sqr(cos(p0.lat) * sin(p1.lat) - sin(p0.lat) * cos(p1.lat) * cos(p1.lon - p0.lon)))
		/ (sin(p0.lat) * sin(p1.lat) + cos(p0.lat) * cos(p1.lat) * cos(p1.lon - p0.lon)));
}

/// Calculates distance of two points on earth, approximated as sphere.
///
/// @param[in] p0 Start point.
/// @param[in] p1 Destination point.
/// @return The distance in meters.
double distance_sphere(const position & p0, const position & p1)
{
	return EARTH_RADIUS * central_spherical_angle(p0, p1);
}

double distance_ellipsoid_vincenty(
	const position & p0, const position & p1, double & alpha1, double & alpha2)
{
	// see inverse.pdf, inverse formulae
	// http://en.wikipedia.org/wiki/Vincenty%27s_formulae

	if (p0.lat == p1.lat && p0.lon == p1.lon)
		return 0.0;

	const double f = EARTH_FLATTENING;
	const double a = EARTH_SEMI_MAJOR_AXIS;
	const double b = (1.0 - f) * a;

	const double L = p1.lon - p0.lon;
	const double U1 = atan((1.0 - f) * tan(p0.lat));
	const double U2 = atan((1.0 - f) * tan(p1.lat));

	double lambda = L;
	double d_lambda = fabs(lambda);

	const double sin_U1 = sin(U1);
	const double sin_U2 = sin(U2);
	const double cos_U1 = cos(U1);
	const double cos_U2 = cos(U2);

	double sin_lambda = 0.0;
	double cos_lambda = 0.0;
	double sigma = 0.0;
	double sin_sqr_sigma = 0.0;
	double sin_sigma = 0.0;
	double cos_sigma = 0.0;
	double cos_sqr_alpha = 0.0;
	double cos_2_sigma_m = 0.0;
	double cos_sqr_2_sigma_m = 0.0;
	double sin_alpha = 0.0;
	double C = 0.0;
	double u_sqr = 0.0;
	double A = 0.0;
	double B = 0.0;
	double d_sigma = 0.0;
	double s = 0.0;
	double old_lambda = 0.0;

	for (int iteration = 0; (iteration < 200) && (d_lambda > 1.0e-12); ++iteration) {
		sin_lambda = sin(lambda);
		cos_lambda = cos(lambda);

		sin_sqr_sigma = sqr(cos_U2 * sin_lambda)
			+ sqr(cos_U1 * sin_U2 - sin_U1 * cos_U2 * cos_lambda); // eq 14
		sin_sigma = sqrt(sin_sqr_sigma); // aquire sin(sigma)
		cos_sigma = sin_U1 * sin_U2 + cos_U1 * cos_U2 * cos_lambda; // eq 15
		sigma = atan(sin_sigma / cos_sigma); // aquire sigma
		sin_alpha = cos_U1 * cos_U2 * sin_lambda / sin_sigma; // eq 17
		cos_sqr_alpha = 1.0 - sqr(sin_alpha); // aquire cos^2(alpha), prevent numerical problems
		cos_2_sigma_m = cos_sigma - (2.0 * sin_U1 * sin_U2) / cos_sqr_alpha; // eq 18
		cos_sqr_2_sigma_m = sqr(cos_2_sigma_m);
		C = f / 16.0 * cos_sqr_alpha * (4.0 + f * (4.0 - 3.0 * cos_sqr_alpha)); // eq 10
		old_lambda = lambda; // save current lambda to calc d_lambda
		lambda = L
			+ (1.0 - C) * f * sin_alpha
				* (sigma
					  + C * sin_sigma
						  * (cos_2_sigma_m
								+ C * cos_sigma * (-1.0 + 2.0 * cos_sqr_2_sigma_m))); // eq 11
		d_lambda = fabs(old_lambda - lambda);
	}

	u_sqr = cos_sqr_alpha * (sqr(a) - sqr(b)) / sqr(b);
	A = 1.0
		+ u_sqr / 16384.0
			* (4096.0 + u_sqr * (-768.0 + u_sqr * (320.0 - 175.0 * u_sqr))); // eq 3
	B = u_sqr / 1024.0 * (256.0 + u_sqr * (-128.0 + u_sqr * (74.0 - 47.0 * u_sqr))); // eq 4
	d_sigma = B * sin_sigma
		* (cos_2_sigma_m + B / 4.0 * (cos_sigma * (-1.0 + 2.0 * cos_sqr_2_sigma_m))
				  - B / 6.0 * cos_2_sigma_m * (-3.0 + 4.0 * sin_sqr_sigma)
					  * (-3.0 + 4.0 * cos_sqr_2_sigma_m)); // eq 6
	s = A * b * (sigma - d_sigma); // eq 7
	alpha1 = atan((cos_U2 * sin_lambda) / (cos_U1 * sin_U2 - sin_U1 * cos_U2 * cos_lambda));
	alpha2 = atan((cos_U1 * sin_lambda) / (-sin_U1 * cos_U2 + cos_U1 * sin_U2 * cos_lambda));

	return s;
}

position point_ellipsoid_vincenty(const position & p0, double s, double alpha1, double & alpha2)
{
	// see inverse.pdf, direct formulae
	// http://en.wikipedia.org/wiki/Vincenty%27s_formulae

	if (fabs(s) < 1.0e-10)
		return p0;

	const double f = EARTH_FLATTENING;
	const double a = EARTH_SEMI_MAJOR_AXIS;
	const double b = (1.0 - f) * a;

	const double sin_alpha1 = sin(alpha1);
	const double cos_alpha1 = cos(alpha1);

	const double tan_U1 = (1.0 - f) * tan(p0.lat);
	const double U1 = atan(tan_U1);

	const double sin_U1 = sin(U1);
	const double cos_U1 = cos(U1);

	const double sigma1 = atan(tan_U1 / cos_alpha1);

	const double sin_alpha = cos(U1) * sin_alpha1;
	const double sin_sqr_alpha = sqr(sin_alpha);

	const double cos_sqr_alpha = (1.0 - sin_alpha) * (1.0 + sin_alpha);

	const double u_sqr = cos_sqr_alpha * (sqr(a) - sqr(b)) / sqr(b);

	const double A = 1.0
		+ u_sqr / 16384.0
			* (4096.0 + u_sqr * (-768.0 + u_sqr * (320.0 - 175.0 * u_sqr))); // eq 3

	const double B = u_sqr / 1024.0
		* (256.0 + u_sqr * (-128.0 + u_sqr * (74.0 - 47.0 * u_sqr))); // eq 4

	double sigma_0 = s / (b * A);
	double sigma = sigma_0;

	double d_sigma = fabs(sigma);

	double sin_sigma = 0.0;
	double cos_sigma = 0.0;
	double cos_2_sigma_m = 0.0;
	double cos_sqr_2_sigma_m = 0.0;
	double old_sigma = 0.0;
	double delta_sigma = 0.0;
	double lambda = 0.0;
	double C = 0.0;
	double L = 0.0;

	for (int iteration = 0; (iteration < 200) && (d_sigma > 1.0e-12); ++iteration) {
		cos_2_sigma_m = cos(2.0 * sigma1 + sigma);
		cos_sqr_2_sigma_m = sqr(cos_2_sigma_m);
		cos_sigma = cos(sigma);
		sin_sigma = sin(sigma);
		delta_sigma
			= B * sin_sigma
			* (cos_2_sigma_m
				  + B / 4.0 * (cos_sigma * (-1.0 + 2.0 * cos_sqr_2_sigma_m)
								  - B / 6.0 * cos_2_sigma_m * (-3.0 + 4.0 * sqr(sin_sigma))
									  * (-3.0 + 4.0 * cos_sqr_2_sigma_m)));

		old_sigma = sigma;
		sigma = sigma_0 + delta_sigma;
		d_sigma = fabs(old_sigma - sigma);
	}

	position p1;

	p1.lat = atan((sin_U1 * cos_sigma + cos_U1 * sin_sigma * cos_alpha1)
		/ ((1.0 - f) * sqrt(sin_sqr_alpha
						   + sqr(sin_U1 * sin_sigma - cos_U1 * cos_sigma * cos_alpha1))));
	C = (f / 16.0) * cos_sqr_alpha * (4.0 + f * (4.0 - 3.0 * cos_sqr_alpha));
	lambda = atan(
		(sin_sigma * sin_alpha1) / (cos_U1 * cos_sigma - sin_U1 * sin_sigma * cos_alpha1));
	L = lambda
		- (1.0 - C) * f * sin_alpha
			* (sigma
				  + C * sin_sigma
					  * (cos_2_sigma_m + C * cos_sigma * (-1.0 + 2.0 * cos_sqr_2_sigma_m)));
	p1.lon = p0.lon + L;
	alpha2 = atan(sin_alpha / (-sin_U1 * sin_sigma + cos_U1 * cos_sigma * cos_alpha1));

	return p1;
}

double distance_ellipsoid_lambert(const position & p0, const position & p1)
{
	const double r = 1.0 / EARTH_FLATTENING;

	position t1 = {atan((r - 1.0) / r) * tan(p0.lat), p0.lon};
	position t2 = {atan((r - 1.0) / r) * tan(p1.lat), p1.lon};

	const double sigma = central_spherical_angle(t1, t2);

	const double P = (t1.lat + t2.lat) / 2.0;

	const double Q = (t2.lat - t1.lat) / 2.0;

	const double X = (sigma - sin(sigma)) * (sqr(sin(P)) * sqr(cos(Q))) / sqr(cos(sigma / 2.0));

	const double Y = (sigma + sin(sigma)) * (sqr(cos(P)) * sqr(sin(Q))) / sqr(sin(sigma / 2.0));

	return EARTH_RADIUS * (sigma - (X + Y) / (2.0 * r));
}
}
}
