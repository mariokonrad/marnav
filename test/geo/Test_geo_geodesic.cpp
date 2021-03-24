#include <marnav/geo/geodesic.hpp>
#include <marnav/math/constants.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;
using marnav::math::pi;

class Test_geo_geodesic : public ::testing::Test
{
};

TEST_F(Test_geo_geodesic, central_spherical_angle_default_constructed)
{
	geo::position p0;
	geo::position p1;

	auto d = geo::central_spherical_angle(p0, p1);

	EXPECT_NEAR(d, 0.0, 1e-6);
}

TEST_F(Test_geo_geodesic, central_spherical_angle)
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

TEST_F(Test_geo_geodesic, distance_sphere)
{
	const geo::position BNA = {36.12, -86.67};
	const geo::position LAX = {33.94, -118.40};

	const double expected = 2889615.861940;
	// exact would be     : 2892777.232346 m

	auto result = geo::distance_sphere(BNA, LAX);

	EXPECT_NEAR(expected, result.distance, 1e-3);
}

TEST_F(Test_geo_geodesic, distance_ellipsoid_vincenty_BNA_LAX)
{
	const geo::position BNA = {36.12, -86.67};
	const geo::position LAX = {33.94, -118.40};

	const double expected = 2892777.2323462227;
	// exact would be     : 2892777.232346 m

	auto result = geo::distance_ellipsoid_vincenty(BNA, LAX);

	EXPECT_NEAR(expected, result.distance, 1e-3);
}

TEST_F(Test_geo_geodesic, distance_ellipsoid_vincenty_same_longitude)
{
	const geo::position p1 = {00.0, 0.0};
	const geo::position p2 = {30.0, 0.0};

	// test value computed using: http://www.ga.gov.au/geodesy/datums/vincenty_inverse.jsp
	const double expected = 3320113.398; // [m]

	auto result = geo::distance_ellipsoid_vincenty(p1, p2);

	EXPECT_NEAR(expected, result.distance, 0.1);
}

TEST_F(Test_geo_geodesic, distance_ellipsoid_vincenty_same_latitude)
{
	const geo::position p1 = {0.0, 0.0};
	const geo::position p2 = {0.0, 30.0};

	// test value computed using: http://www.ga.gov.au/geodesy/datums/vincenty_inverse.jsp
	const double expected = 3339584.724; // [m]

	auto result = geo::distance_ellipsoid_vincenty(p1, p2);

	EXPECT_NEAR(expected, result.distance, 0.1);
}

TEST_F(Test_geo_geodesic, distance_ellipsoid_lambert)
{
	const geo::position BNA = {36.12, -86.67};
	const geo::position LAX = {33.94, -118.40};

	const double expected = 3013798.3235893762;
	// exact would be     : 2892777.232346 m

	auto result = geo::distance_ellipsoid_lambert(BNA, LAX);

	EXPECT_NEAR(expected, result.distance, 1e-3);
}

TEST_F(Test_geo_geodesic, point_ellipsoid_vincenty)
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
