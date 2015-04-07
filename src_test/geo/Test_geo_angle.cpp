#include <gtest/gtest.h>
#include <geo/angle.hpp>

namespace
{

using namespace marnav;

class Test_geo_angle : public ::testing::Test
{
};

TEST_F(Test_geo_angle, construction_default) { geo::angle{}; }

TEST_F(Test_geo_angle, construction_value) { geo::angle{1.0}; }

TEST_F(Test_geo_angle, comparison)
{
	geo::angle a{1.0};
	geo::angle b{1.0};
	geo::angle c{2.0};

	EXPECT_TRUE(a == a);
	EXPECT_TRUE(b == b);
	EXPECT_TRUE(c == c);

	EXPECT_TRUE(a == b);
	EXPECT_TRUE(b == a);
	EXPECT_FALSE(a == c);
	EXPECT_FALSE(c == a);
	EXPECT_FALSE(b == c);
	EXPECT_FALSE(c == b);
}

TEST_F(Test_geo_angle, degrees)
{
	EXPECT_EQ(0u, geo::angle{0.0}.degrees());
	EXPECT_EQ(1u, geo::angle{1.0}.degrees());
	EXPECT_EQ(2u, geo::angle{2.0}.degrees());
	EXPECT_EQ(10u, geo::angle{10.0}.degrees());
}

TEST_F(Test_geo_angle, minutes)
{
	EXPECT_EQ(0u, geo::angle{0.0}.minutes());
	EXPECT_EQ(30u, geo::angle{0.5}.minutes());
}

TEST_F(Test_geo_angle, seconds)
{
	EXPECT_NEAR(0.00, geo::angle{0.0000}.seconds(), 1e-4);
	EXPECT_NEAR(0.72, geo::angle{0.0002}.seconds(), 1e-4);
	EXPECT_NEAR(1.80, geo::angle{0.0005}.seconds(), 1e-4);
	EXPECT_NEAR(3.60, geo::angle{0.0010}.seconds(), 1e-4);
}

TEST_F(Test_geo_angle, latitude_invalid_value) { EXPECT_ANY_THROW(geo::latitude{91.0}); }

TEST_F(Test_geo_angle, longitude_invalid_value) { EXPECT_ANY_THROW(geo::longitude{181.0}); }

TEST_F(Test_geo_angle, latitude_hemisphere)
{
	EXPECT_EQ(geo::latitude::hemisphere::NORTH, geo::latitude{+1.0}.hem());
	EXPECT_EQ(geo::latitude::hemisphere::SOUTH, geo::latitude{-1.0}.hem());
}

TEST_F(Test_geo_angle, longitude_hemisphere)
{
	EXPECT_EQ(geo::longitude::hemisphere::WEST, geo::longitude{+1.0}.hem());
	EXPECT_EQ(geo::longitude::hemisphere::EAST, geo::longitude{-1.0}.hem());
}
}
