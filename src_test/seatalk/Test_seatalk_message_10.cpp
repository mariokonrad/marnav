#include <gtest/gtest.h>
#include <seatalk/message_10.hpp>

namespace
{
class Test_seatalk_message_10 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_10, construction)
{
	seatalk::message_10 m;
}

TEST_F(Test_seatalk_message_10, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_10::parse({3, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_10::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_10, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_10::parse({0x10, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_10::parse({0x10, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_10, parse)
{
	struct test_case
	{
		seatalk::raw data;
		uint16_t angle;
	};

	std::vector<test_case> cases{
		{{0x10, 0x01, 0x00, 0x00}, 0}, //  0.0 deg
		{{0x10, 0x01, 0x00, 0x01}, 5}, //  0.5 deg
		{{0x10, 0x01, 0x00, 0x02}, 10}, //  1.0 deg
		{{0x10, 0x01, 0x00, 0x03}, 15}, //  1.5 deg
		{{0x10, 0x01, 0x00, 0x04}, 20}, //  2.0 deg
		{{0x10, 0x01, 0x00, 0x14}, 100}, // 10.0 deg
		{{0x10, 0x01, 0x00, 0xb4}, 900}, // 90.0 deg
	};

	for (auto const& t : cases) {
		auto generic_message = seatalk::message_10::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = seatalk::message_cast<seatalk::message_10>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(seatalk::message_id::apparent_wind_angle, m->type());
		EXPECT_EQ(t.angle, m->get_angle());
	}
}

TEST_F(Test_seatalk_message_10, write_default)
{
	const seatalk::raw expected{0x10, 0x01, 0x00, 0x00};
	seatalk::message_10 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_10, write_angle)
{
	const seatalk::raw expected{0x10, 0x01, 0x01, 0x00};
	seatalk::message_10 m;
	m.set_angle(1);

	EXPECT_EQ(expected, m.get_data());
}

}
