#include <gtest/gtest.h>
#include <marnav/geo/greatcircle.hpp>

namespace
{
using namespace marnav;

class Test_geo_greatcircle : public ::testing::Test
{
};

TEST_F(Test_geo_greatcircle, central_spherical_angle_default_constructed)
{
	geo::position p0;
	geo::position p1;

	auto d = geo::central_spherical_angle(p0, p1);

	EXPECT_NEAR(d, 0.0, 1e-6);
}

TEST_F(Test_geo_greatcircle, central_spherical_angle)
{
	struct test_data {
		geo::position p0;
		geo::position p1;
		double angle;
	};

	static const test_data DATA[] = {
		{{0.0, 0.0}, {0.0, 0.0}, 0.0},
		{{1.0, 0.0}, {0.0, 0.0}, 1.0},
		{{0.0, 1.0}, {0.0, 0.0}, 1.0},
		{{0.0, 0.0}, {1.0, 0.0}, 1.0},
		{{0.0, 0.0}, {0.0, 1.0}, 1.0},
	};

	for (auto const & item : DATA) {
		auto d = geo::central_spherical_angle(item.p0, item.p1);
		EXPECT_NEAR(d, item.angle, 1e-6);
	}
}

// TODO: more tests

}
