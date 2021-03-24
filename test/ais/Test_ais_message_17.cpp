#include <marnav/ais/message_17.hpp>
#include <marnav/ais/ais.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class Test_ais_message_17 : public ::testing::Test
{
};

TEST_F(Test_ais_message_17, parse)
{
	std::vector<std::pair<std::string, uint32_t>> v
		= {{"A02VqLPA4I6C07h5Ed1h<OrsuBTTwS?r:C?w`?la<gno1RTRwSP9:BcurA8a", 0},
			{":Oko02TSwu8<:Jbb", 0}};

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_17>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(0u, m->get_repeat_indicator());
	EXPECT_EQ(2734450u, m->get_mmsi());

	// Longitude: 17478
	EXPECT_NEAR(29.13, *m->get_lon(), 1e-4);

	// Latitude: 35992
	EXPECT_NEAR(59.98666667, *m->get_lat(), 1e-4);

	// DGNSS data:
	// 376:7c0556c07031febbf52924fe33fa2933ffa0fd2932fdb7062922fe3809292afde9122929fcf7002923ffd20c29aaaa
	EXPECT_EQ(376u, m->get_payload().size());
}

TEST_F(Test_ais_message_17, parse_negative_latitude)
{
	std::vector<std::pair<std::string, uint32_t>> v
		= {{"A;wUJKU>io;WlWuwH`W1PpnuN<isf;5iHtOM1S6q?vsvNrNGOqLcr5mfD6t", 2}};

	auto result = ais::make_message(v);
	ASSERT_TRUE(result != nullptr);

	auto m = ais::message_cast<ais::message_17>(result);
	ASSERT_TRUE(m != nullptr);

	EXPECT_EQ(0u, m->get_repeat_indicator());
	EXPECT_EQ(804870766u, m->get_mmsi());

	// Longitude: 80669
	EXPECT_NEAR(134.44833, *m->get_lon(), 1e-4);

	// Latitude:-26818
	EXPECT_NEAR(-44.69666667, *m->get_lat(), 1e-4);

	// DGNSS data: 272:7f7f6289c1838dbd78cc7bb8b17163c7dd0631b93feefe7ba7977f972be85d6e506f
	EXPECT_EQ(272u, m->get_payload().size());
}

TEST_F(Test_ais_message_17, encode_default_values)
{
	ais::message_17 m;

	auto v = ais::encode_message(m);

	ASSERT_EQ(1u, v.size());
	EXPECT_STREQ("A000001b3Qba00", v[0].first.c_str());
	EXPECT_EQ(4u, v[0].second);
}

TEST_F(Test_ais_message_17, wrong_number_of_bits)
{
	EXPECT_ANY_THROW(ais::message_parse<ais::message_17>(ais::raw(79)));
	EXPECT_ANY_THROW(ais::message_parse<ais::message_17>(ais::raw(817)));
}
}
