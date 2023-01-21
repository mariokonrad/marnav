#include <marnav/ais/message.hpp>
#include <marnav/ais/message_01.hpp>
#include <marnav/ais/message_05.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;

class test_ais_message : public ::testing::Test
{
};

TEST_F(test_ais_message, message_cast_nullptr)
{
	std::unique_ptr<ais::message> m;
	auto rc = ais::message_cast<ais::message_01>(m);
	EXPECT_EQ(nullptr, rc);
}

TEST_F(test_ais_message, message_cast_wrong_id)
{
	std::unique_ptr<ais::message> m(new ais::message_01);
	EXPECT_ANY_THROW(ais::message_cast<ais::message_05>(m));
}
}
