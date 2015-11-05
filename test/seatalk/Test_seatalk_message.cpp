#include <gtest/gtest.h>
#include <marnav/seatalk/seatalk.hpp>
#include <marnav/seatalk/message_00.hpp>
#include <marnav/seatalk/message_01.hpp>

namespace
{

using namespace marnav;

class Test_seatalk_message : public ::testing::Test
{
};

TEST_F(Test_seatalk_message, message_is_null)
{
	std::unique_ptr<seatalk::message> p;
	auto rc = seatalk::message_cast<seatalk::message_00>(p);

	EXPECT_EQ(nullptr, rc);
}

TEST_F(Test_seatalk_message, message_wrong_id)
{
	std::unique_ptr<seatalk::message> p(new seatalk::message_00);
	EXPECT_ANY_THROW(seatalk::message_cast<seatalk::message_01>(p));
}

TEST_F(Test_seatalk_message, message_size)
{
	EXPECT_TRUE(seatalk::message_size(seatalk::message_id::depth_below_transducer) != 0u);
}

TEST_F(Test_seatalk_message, message_size_invalid_message)
{
	EXPECT_ANY_THROW(seatalk::message_size(static_cast<seatalk::message_id>(-1)));
}
}
