#include <gtest/gtest.h>
#include <marnav/seatalk/message_38.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_38 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_38, construction)
{
	message_38 m;
}

TEST_F(Test_seatalk_message_38, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_38::parse({3, 0x00}));
	EXPECT_ANY_THROW(message_38::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_38, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_38::parse({0x38, 0x00, 0x00, 0x01}));
	EXPECT_ANY_THROW(message_38::parse({0x38, 0x02, 0x00, 0x01}));
}

TEST_F(Test_seatalk_message_38, parse)
{
	struct test_case {
		raw data;
	};

	std::vector<test_case> cases{
		{{0x38, 0x01, 0x00, 0x00}},
	};

	for (auto const & t : cases) {
		auto generic_message = message_38::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_38>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
	}
}

TEST_F(Test_seatalk_message_38, write_default)
{
	const raw expected{0x38, 0x01, 0x00, 0x00};
	message_38 m;

	EXPECT_EQ(expected, m.get_data());
}
}
