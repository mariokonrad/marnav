#include <marnav/seatalk/message_52.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_52 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_52, construction)
{
	EXPECT_NO_THROW(message_52 m);
}

TEST_F(Test_seatalk_message_52, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_52::parse({3, 0x00}));
	EXPECT_ANY_THROW(message_52::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_52, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_52::parse({0x52, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_52::parse({0x52, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_52, parse)
{
	struct test_case {
		raw data;
		double sog;
	};

	const std::vector<test_case> cases{
		{{0x52, 0x01, 0x00, 0x01}, 0.1}, {{0x52, 0x01, 0x00, 0x10}, 1.6},
		{{0x52, 0x01, 0x01, 0x00}, 25.6}, {{0x52, 0x01, 0x10, 0x00}, 409.6},
	};

	for (auto const & t : cases) {
		auto generic_message = message_52::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_52>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_NEAR(t.sog, m->get_sog(), 1e-5);
	}
}

TEST_F(Test_seatalk_message_52, write_default)
{
	const raw expected{0x52, 0x01, 0x00, 0x00};
	message_52 m;

	EXPECT_EQ(expected, m.get_data());
}
}
