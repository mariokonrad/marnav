#include <gtest/gtest.h>
#include <marnav/seatalk/message_65.hpp>

namespace
{
using namespace marnav::seatalk;

class Test_seatalk_message_65 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_65, construction)
{
	EXPECT_NO_THROW(message_65 m);
}

TEST_F(Test_seatalk_message_65, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_65::parse({2, 0x00}));
	EXPECT_ANY_THROW(message_65::parse({4, 0x00}));
}

TEST_F(Test_seatalk_message_65, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_65::parse({0x65, 0x01, 0x00}));
}

TEST_F(Test_seatalk_message_65, parse)
{
	auto message = message_65::parse({0x65, 0x00, 0x02});
	ASSERT_TRUE(message != nullptr);
	auto m = message_cast<message_65>(message);
	ASSERT_TRUE(m != nullptr);
}

TEST_F(Test_seatalk_message_65, write_default)
{
	const raw expected{0x65, 0x00, 0x02};
	message_65 m;

	EXPECT_EQ(expected, m.get_data());
}
}
