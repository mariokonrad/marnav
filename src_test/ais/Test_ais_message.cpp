#include <gtest/gtest.h>
#include <ais/message.hpp>
#include <ais/message_01.hpp>
#include <ais/message_05.hpp>

namespace
{
class Test_ais_message : public ::testing::Test
{
};

TEST_F(Test_ais_message, message_cast_nullptr)
{
	std::unique_ptr<ais::message> m;
	auto rc = ais::message_cast<ais::message_01>(m);
	EXPECT_EQ(nullptr, rc);
}

TEST_F(Test_ais_message, message_cast_wrong_id)
{
	std::unique_ptr<ais::message> m(new ais::message_01);
	auto rc = ais::message_cast<ais::message_05>(m);
	EXPECT_EQ(nullptr, rc);
}
}
