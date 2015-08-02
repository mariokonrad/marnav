#include <gtest/gtest.h>
#include <marnav/geo/cpa.hpp>

using namespace marnav::geo;

namespace
{

class Test_geo_cpa : public ::testing::Test
{
};

TEST_F(Test_geo_cpa, collision_on_equator)
{
	const vessel vessel1 = {{0.0, 1.0}, 1.0, 90.0}; // going east
	const vessel vessel2 = {{0.0, -1.0}, 1.0, 270.0}; // going west

	// 2 degrees appart = 120nm, closing in at each 1kn => 60h
	const position expected_vessels_pos{0.0, 0.0};
	const std::chrono::seconds expected_time{60 * 3600};

	position p1;
	position p2;
	std::chrono::seconds t;
	std::tie(p1, p2, t) = cpa(vessel1, vessel2);

	EXPECT_EQ(expected_vessels_pos, p1);
	EXPECT_EQ(expected_vessels_pos, p2);
	EXPECT_EQ(p1, p2);
	EXPECT_EQ(expected_time, t);
}

}
