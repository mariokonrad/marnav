#include <marnav/seatalk/message_26.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav;

class Test_seatalk_message_26 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_26, construction)
{
	seatalk::message_26 m;
}

TEST_F(Test_seatalk_message_26, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_26::parse({6, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_26::parse({8, 0x00}));
}

TEST_F(Test_seatalk_message_26, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_26::parse({0x26, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_26::parse({0x26, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_26, parse)
{
	struct test_case {
		seatalk::raw data;
	};

	std::vector<test_case> cases{
		{{0x26, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00}},
	};

	for (auto const & t : cases) {
		auto generic_message = seatalk::message_26::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = seatalk::message_cast<seatalk::message_26>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(seatalk::message_id::speed_through_water_2, m->type());
	}
}
}
