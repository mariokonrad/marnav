#include <gtest/gtest.h>
#include <marnav/geo/region.hpp>

namespace
{

using namespace marnav::geo;

class Test_geo_region : public ::testing::Test
{
};

TEST_F(Test_geo_region, construction)
{
	region reg{
		{0.0, 0.0}, // top left, equator/greenwitch
		{-2.0, -3.0} // bottom right, south of equator/east of greenwitch
	};

	const auto w = reg.left();
	const auto e = reg.right();
	EXPECT_TRUE(w > e) << "westerly:" << w << ", easterly: " << e;

	const auto n = reg.top();
	const auto s = reg.bottom();
	EXPECT_TRUE(n > s) << "northern:" << n << ", southern:" << s;
}

TEST_F(Test_geo_region, construction_left_right_reversed)
{
	region reg{
		{0.0, -3.0}, // top left, equator/greenwitch
		{-2.0, 0.0} // bottom right, south of equator/east of greenwitch
	};

	const auto w = reg.left();
	const auto e = reg.right();
	EXPECT_TRUE(w > e) << "westerly:" << w << ", easterly: " << e;

	const auto n = reg.top();
	const auto s = reg.bottom();
	EXPECT_TRUE(n > s) << "northern:" << n << ", southern:" << s;
}

TEST_F(Test_geo_region, construction_top_bottom_reversed)
{
	region reg{
		{-2.0, 0.0}, // top left, equator/greenwitch
		{0.0, -3.0} // bottom right, south of equator/east of greenwitch
	};

	const auto w = reg.left();
	const auto e = reg.right();
	EXPECT_TRUE(w > e) << "westerly:" << w << ", easterly: " << e;

	const auto n = reg.top();
	const auto s = reg.bottom();
	EXPECT_TRUE(n > s) << "northern:" << n << ", southern:" << s;
}

TEST_F(Test_geo_region, inside)
{
	region reg{
		{0.0, 0.0}, // top left, equator/greenwitch
		{-2.0, -3.0} // bottom right, south of equator/east of greenwitch
	};

	EXPECT_TRUE(reg.inside({0.0, 0.0}));
	EXPECT_TRUE(reg.inside({-2.0, 0.0}));
	EXPECT_TRUE(reg.inside({0.0, -3.0}));
	EXPECT_TRUE(reg.inside({-2.0, -3.0}));

	EXPECT_TRUE(reg.inside({-1.0, -1.0}));
}

}
