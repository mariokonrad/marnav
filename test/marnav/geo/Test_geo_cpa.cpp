#include <marnav/geo/cpa.hpp>
#include <gtest/gtest.h>

using namespace marnav::geo;

namespace
{

class test_geo_cpa : public ::testing::Test
{
};

TEST_F(test_geo_cpa, collision_on_equator_eastwards_westwards)
{
	const vessel vessel1 = {{0.0, 1.0}, 1.0, 90.0}; // being west, going east
	const vessel vessel2 = {{0.0, -1.0}, 1.0, 270.0}; // being east, going west

	// 2 degrees appart = 120nm, closing in at each 1kn => 60h
	const position expected_vessels_pos{0.0, 0.0};
	const std::chrono::seconds expected_time{60 * 3600};

	position p1;
	position p2;
	std::chrono::seconds tcpa;
	bool cpa_exists;
	std::tie(p1, p2, tcpa, cpa_exists) = cpa(vessel1, vessel2);

	EXPECT_NEAR(expected_vessels_pos.lat(), p1.lat(), 1e-5);
	EXPECT_NEAR(expected_vessels_pos.lon(), p1.lon(), 1e-5);
	EXPECT_NEAR(expected_vessels_pos.lat(), p2.lat(), 1e-5);
	EXPECT_NEAR(expected_vessels_pos.lon(), p2.lon(), 1e-5);
	EXPECT_NEAR(p1.lat(), p2.lat(), 1e-5);
	EXPECT_NEAR(p1.lon(), p2.lon(), 1e-5);
	EXPECT_EQ(expected_time, tcpa);
	EXPECT_TRUE(cpa_exists);
}

TEST_F(test_geo_cpa, collision_on_equator_eastwards_northwards)
{
	const vessel vessel1 = {{0.0, 1.0}, 1.0, 90.0}; // being west, going east
	const vessel vessel2 = {{-1.0, 0.0}, 1.0, 0.0}; // being south, going north

	// each vessel 1 degree appart from CPA = 60nm, closing in at 1kn => 60h
	const position expected_vessels_pos{0.0, 0.0};
	const std::chrono::seconds expected_time{60 * 3600};

	position p1;
	position p2;
	std::chrono::seconds tcpa;
	bool cpa_exists;
	std::tie(p1, p2, tcpa, cpa_exists) = cpa(vessel1, vessel2);

	EXPECT_NEAR(expected_vessels_pos.lat(), p1.lat(), 1e-5);
	EXPECT_NEAR(expected_vessels_pos.lon(), p1.lon(), 1e-5);
	EXPECT_NEAR(expected_vessels_pos.lat(), p2.lat(), 1e-5);
	EXPECT_NEAR(expected_vessels_pos.lon(), p2.lon(), 1e-5);
	EXPECT_NEAR(p1.lat(), p2.lat(), 1e-5);
	EXPECT_NEAR(p1.lon(), p2.lon(), 1e-5);
	EXPECT_EQ(expected_time, tcpa);
	EXPECT_EQ(std::chrono::minutes(60 * 60), tcpa);
	EXPECT_EQ(std::chrono::hours(60), tcpa);
	EXPECT_TRUE(cpa_exists);
}
}
