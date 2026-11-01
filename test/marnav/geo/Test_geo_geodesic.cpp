#include <marnav/geo/geodesic.hpp>
#include <marnav/math/constants.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;
using marnav::math::pi;

class test_geo_geodesic : public ::testing::Test
{
};

TEST_F(test_geo_geodesic, central_spherical_angle_default_constructed)
{
	geo::position p0;
	geo::position p1;

	auto d = geo::central_spherical_angle(p0, p1);

	EXPECT_NEAR(d, 0.0, 1e-6);
}

TEST_F(test_geo_geodesic, central_spherical_angle)
{
	struct test_data {
		geo::position p0;
		geo::position p1;
		double angle_rad;
	};

	static const test_data DATA[] = {
		{{0.0, 0.0}, {0.0, 0.0}, 0.0 * pi / 180.0},
		{{45.0, 0.0}, {0.0, 0.0}, 45.0 * pi / 180.0},
		{{0.0, 45.0}, {0.0, 0.0}, 45.0 * pi / 180.0},
		{{0.0, 0.0}, {45.0, 0.0}, 45.0 * pi / 180.0},
		{{0.0, 0.0}, {0.0, 45.0}, 45.0 * pi / 180.0},
	};

	for (auto const & item : DATA) {
		auto d = geo::central_spherical_angle(item.p0, item.p1);
		EXPECT_NEAR(d, item.angle_rad, 1e-6);
	}
}

TEST_F(test_geo_geodesic, distance_sphere)
{
	const geo::position BNA = {36.12, -86.67};
	const geo::position LAX = {33.94, -118.40};

	const double expected = 2889615.861940;
	// exact would be     : 2892777.232346 m

	auto result = geo::distance_sphere(BNA, LAX);

	EXPECT_NEAR(expected, result.distance, 1e-3);
}

TEST_F(test_geo_geodesic, distance_ellipsoid_vincenty_BNA_LAX)
{
	const geo::position BNA = {36.12, -86.67};
	const geo::position LAX = {33.94, -118.40};

	const double expected = 2892777.2323462227;
	// exact would be     : 2892777.232346 m

	auto result = geo::distance_ellipsoid_vincenty(BNA, LAX);

	EXPECT_NEAR(expected, result.distance, 1e-3);
}

TEST_F(test_geo_geodesic, distance_ellipsoid_vincenty_same_longitude)
{
	const geo::position p1 = {00.0, 0.0};
	const geo::position p2 = {30.0, 0.0};

	// test value computed using: http://www.ga.gov.au/geodesy/datums/vincenty_inverse.jsp
	const double expected = 3320113.398; // [m]

	auto result = geo::distance_ellipsoid_vincenty(p1, p2);

	EXPECT_NEAR(expected, result.distance, 0.1);
}

TEST_F(test_geo_geodesic, distance_ellipsoid_vincenty_same_latitude)
{
	const geo::position p1 = {0.0, 0.0};
	const geo::position p2 = {0.0, 30.0};

	// test value computed using: http://www.ga.gov.au/geodesy/datums/vincenty_inverse.jsp
	const double expected = 3339584.724; // [m]

	auto result = geo::distance_ellipsoid_vincenty(p1, p2);

	EXPECT_NEAR(expected, result.distance, 0.1);
}

TEST_F(test_geo_geodesic, distance_ellipsoid_lambert)
{
	const geo::position BNA = {36.12, -86.67};
	const geo::position LAX = {33.94, -118.40};

	const double expected = 2892777.04;
	// exact would be     : 2892777.232346 m

	auto result = geo::distance_ellipsoid_lambert(BNA, LAX);

	EXPECT_NEAR(expected, result.distance, 1e-1);
}

TEST_F(test_geo_geodesic, distance_sphere_London_Sydney)
{
	const geo::position London = {51.5, -0.13};
	const geo::position Sydney = {-33.87, 151.21};

	const double expected = 17013284.4;
	// exact would be     : 16989978.8 m

	auto result = geo::distance_sphere(London, Sydney);

	EXPECT_GT(result.distance, 0.0);
	EXPECT_NEAR(expected, result.distance, 1.0);
}

TEST_F(test_geo_geodesic, distance_ellipsoid_lambert_London_Sydney)
{
	const geo::position London = {51.5, -0.13};
	const geo::position Sydney = {-33.87, 151.21};

	const double expected = 16990005.0;
	// exact would be     : 16989978.8 m

	auto result = geo::distance_ellipsoid_lambert(London, Sydney);

	EXPECT_NEAR(expected, result.distance, 50.0);
}

TEST_F(test_geo_geodesic, distance_ellipsoid_lambert_same_point)
{
	static const geo::position DATA[] = {
		{0.0, 0.0},
		{54.0, 10.0},
	};

	for (auto const & p : DATA) {
		auto result = geo::distance_ellipsoid_lambert(p, p);
		EXPECT_NEAR(0.0, result.distance, 1e-6);
	}
}

TEST_F(test_geo_geodesic, point_ellipsoid_vincenty)
{
	struct test_data {
		geo::position start;
		double azimuth;
		double distance;
		geo::position expected;
	};

	static const test_data DATA[] = {
		{{0.0, 0.0}, 0.0 * pi / 180.0, 60 * 1852.0, {1.0049343, 0.0}},
		{{0.0, 0.0}, 90.0 * pi / 180.0, 60 * 1852.0, {0.0, 0.99820794}},
	};

	for (auto const & item : DATA) {
		double alpha2 = 0.0;
		auto destination
			= geo::point_ellipsoid_vincenty(item.start, item.distance, item.azimuth, alpha2);
		EXPECT_NEAR(item.expected.lat(), destination.lat(), 1e-4);
		EXPECT_NEAR(item.expected.lon(), destination.lon(), 1e-4);
	}
}
}
