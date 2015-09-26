#include <gtest/gtest.h>
#include <marnav/seatalk/message_36.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_36 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_36, construction) { message_36 m; }

TEST_F(Test_seatalk_message_36, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_36::parse({1, 0x00}));
	EXPECT_ANY_THROW(message_36::parse({2, 0x00}));
}

TEST_F(Test_seatalk_message_36, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_36::parse({0x36, 0x01, 0x01}));
	EXPECT_ANY_THROW(message_36::parse({0x36, 0x02, 0x01}));
}

TEST_F(Test_seatalk_message_36, parse)
{
	struct test_case {
		raw data;
	};

	std::vector<test_case> cases{
		{{0x36, 0x00, 0x01}},
	};

	for (auto const & t : cases) {
		auto generic_message = message_36::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_36>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(message_id::cancel_mob_condition, m->type());
	}
}

TEST_F(Test_seatalk_message_36, write_default)
{
	const raw expected{0x36, 0x00, 0x01};
	message_36 m;

	EXPECT_EQ(expected, m.get_data());
}
}
