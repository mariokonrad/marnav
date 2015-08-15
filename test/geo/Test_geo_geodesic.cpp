#include <gtest/gtest.h>
#include <marnav/geo/geodesic.hpp>
#include <cmath>

namespace
{
using namespace marnav;

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
		{{0.0, 0.0}, {0.0, 0.0}, 0.0 * M_PI / 180.0},
		{{45.0, 0.0}, {0.0, 0.0}, 45.0 * M_PI / 180.0},
		{{0.0, 45.0}, {0.0, 0.0}, 45.0 * M_PI / 180.0},
		{{0.0, 0.0}, {45.0, 0.0}, 45.0 * M_PI / 180.0},
		{{0.0, 0.0}, {0.0, 45.0}, 45.0 * M_PI / 180.0},
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

	double d = geo::distance_sphere(BNA, LAX);

	EXPECT_NEAR(expected, d, 1e-3);
}

TEST_F(Test_geo_geodesic, distance_ellipsoid_vincenty)
{
	const geo::position BNA = {36.12, -86.67};
	const geo::position LAX = {33.94, -118.40};

	const double expected = 2892777.2323462227;
	// exact would be     : 2892777.232346 m

	double alpha1 = 0.0;
	double alpha2 = 0.0;

	double d = geo::distance_ellipsoid_vincenty(BNA, LAX, alpha1, alpha2);

	EXPECT_NEAR(expected, d, 1e-3);
}

TEST_F(Test_geo_geodesic, distance_ellipsoid_lambert)
{
	const geo::position BNA = {36.12, -86.67};
	const geo::position LAX = {33.94, -118.40};

	const double expected = 3013798.3235893762;
	// exact would be     : 2892777.232346 m

	double d = geo::distance_ellipsoid_lambert(BNA, LAX);

	EXPECT_NEAR(expected, d, 1e-3);
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
		{{0.0, 0.0}, 0.0 * M_PI / 180.0, 60 * 1852.0, {1.0049343, 0.0}},
		{{0.0, 0.0}, 90.0 * M_PI / 180.0, 60 * 1852.0, {0.0, 0.99820794}},
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
