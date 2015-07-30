#include <gtest/gtest.h>
#include <marnav/geo/region.hpp>

namespace
{

using namespace marnav::geo;

class Test_geo_region : public ::testing::Test
{
public:
	region create_arround_zero()
	{
		// note: this ascii art does not use correct projection

		// atlantic ocean, knee of africa, west of Congo

		// a0 (1.0,1.0)
		// +-----------------+
		// |    I            |
		// |    I            |
		// |====*============|  (equator)
		// |    I            |
		// |    I            |
		// +-----------------+
		//      |            a1 (-2.0,-3.0)
		//      zero meridian

		return region{{1.0, 1.0}, {-2.0, -3.0}};
	}

	region create_somewhere_north_west()
	{
		// note: this ascii art does not use correct projection

		// arround Vancouver/Canada

		// a0 (49.0,124.0)
		// +-----------------+
		// |                 |
		// |                 |
		// |                 |
		// |                 |
		// |                 |
		// +-----------------+
		//                   a1 (48.0,122.0)

		return region{{49.0, 124.0}, {48.0, 124.0}};
	}

	region create_somewhere_south_west()
	{
		// note: this ascii art does not use correct projection

		// arround Buenos Airs/Argentina

		// a0 (-33.0,60.0)
		// +-----------------+
		// |                 |
		// |                 |
		// |                 |
		// |                 |
		// |                 |
		// +-----------------+
		//                   a1 (-35.0,56.0)

		return region{{-33.0, 60.0}, {-35.0, 56.0}};
	}

	region create_date_barrier_south()
	{
		// note: this ascii art does not use correct projection

		// southern hemisphere, arround date barrier, east of New Zealand

		// a0 (-40.0,-178.0)
		// +--------I--------+
		// |        I        |
		// |        I        |
		// |        I        |
		// |        I        |
		// |        I        |
		// +--------I--------+
		//          |        a1 (-45.0,178.0)
		//          date barrier

		return region{{-40.0, -178.0}, {-45.0, 178.0}};
	}

	region create_north_pole()
	{
		// note: this ascii art does not use correct projection

		// a0 (90.0,120.0)
		// +---*-------------+
		// |   I             |
		// |   I             |
		// |   I             |
		// |   I             |
		// |   I             |
		// +-----------------+
		//     |             a1 (80.0, -35.0)
		//     zero meridian

		return region{{80.0, 120.0}, {80.0, -35.0}};
	}
};

TEST_F(Test_geo_region, construction_two_points)
{
	const auto reg = create_arround_zero();

	const auto w = reg.left();
	const auto e = reg.right();
	EXPECT_TRUE(w > e) << "westerly:" << w << ", easterly: " << e;

	const auto n = reg.top();
	const auto s = reg.bottom();
	EXPECT_TRUE(n > s) << "northern:" << n << ", southern:" << s;
}

TEST_F(Test_geo_region, construction_two_points_same_points)
{
	const position p{10.0, 20.0};

	EXPECT_ANY_THROW((region{p, p}));
}

TEST_F(Test_geo_region, construction_two_points_upside_down)
{
	const position p0{-10.0, 20.0};
	const position p1{10.0, 15.0};

	EXPECT_ANY_THROW((region{p0, p1}));
}

TEST_F(Test_geo_region, construction_point_delta)
{
	const auto reg = region{{0.0, 0.0}, 10.0, 5.0};

	EXPECT_EQ(latitude{0.0}, reg.top());
	EXPECT_EQ(latitude{-10.0}, reg.bottom());
	EXPECT_EQ(longitude{0.0}, reg.left());
	EXPECT_EQ(longitude{-5.0}, reg.right());
}

TEST_F(Test_geo_region, construction_point_delta_date_barrier)
{
	const auto reg = region{{0.0, -178.0}, 10.0, 5.0}; // wrap arround E->W at datum barrier

	EXPECT_EQ(latitude{0.0}, reg.top());
	EXPECT_EQ(latitude{-10.0}, reg.bottom());
	EXPECT_EQ(longitude{-178.0}, reg.left());
	EXPECT_EQ(longitude{177.0}, reg.right());
}

TEST_F(Test_geo_region, inside_arround_zero)
{
	const auto reg = create_arround_zero();

	// boundaries
	EXPECT_TRUE(reg.inside({reg.top(), reg.left()}));
	EXPECT_TRUE(reg.inside({reg.top(), reg.right()}));
	EXPECT_TRUE(reg.inside({reg.bottom(), reg.left()}));
	EXPECT_TRUE(reg.inside({reg.bottom(), reg.right()}));

	// random position
	EXPECT_TRUE(reg.inside({0.5, 0.5})); // north west
	EXPECT_TRUE(reg.inside({-1.0, -1.0})); // south east
	EXPECT_FALSE(reg.inside({-3.0, 0.0}));
}

TEST_F(Test_geo_region, inside_date_barrier)
{
	const auto reg = create_date_barrier_south();

	// boundaries
	EXPECT_TRUE(reg.inside({reg.top(), reg.left()}));
	EXPECT_TRUE(reg.inside({reg.top(), reg.right()}));
	EXPECT_TRUE(reg.inside({reg.bottom(), reg.left()}));
	EXPECT_TRUE(reg.inside({reg.bottom(), reg.right()}));

	// random position
	EXPECT_FALSE(reg.inside({0.0, 0.0}));
	EXPECT_TRUE(reg.inside({-42.0, 180.0}));
	EXPECT_FALSE(reg.inside({-42.0, -177.5}));
}
}
