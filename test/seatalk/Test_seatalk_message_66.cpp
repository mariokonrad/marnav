#include <gtest/gtest.h>
#include <marnav/seatalk/message_66.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_66 : public ::testing::Test
{
public:
	using alarm = message_66::alarm;

	struct test_case {
		raw data;
		alarm a;
	};

	const std::vector<test_case> cases{
		{{0x66, 0x00, 0x00}, alarm::no_alarm},
		{{0x66, 0x00, 0x80}, alarm::apparent_angle_lo},
		{{0x66, 0x00, 0x40}, alarm::apparent_angle_hi},
		{{0x66, 0x00, 0x20}, alarm::apparent_speed_lo},
		{{0x66, 0x00, 0x10}, alarm::apparent_speed_hi},
		{{0x66, 0x00, 0x08}, alarm::true_angle_lo},
		{{0x66, 0x00, 0x04}, alarm::true_angle_hi},
		{{0x66, 0x00, 0x02}, alarm::true_speed_lo},
		{{0x66, 0x00, 0x01}, alarm::true_speed_hi},
		{{0x66, 0x00, 0x05}, alarm::true_angle_hi | alarm::true_speed_hi},
	};
};

TEST_F(Test_seatalk_message_66, construction) { EXPECT_NO_THROW(message_66 m); }

TEST_F(Test_seatalk_message_66, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_66::parse({7, 0x00}));
	EXPECT_ANY_THROW(message_66::parse({9, 0x00}));
}

TEST_F(Test_seatalk_message_66, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_66::parse({0x66, 0x01, 0x00}));
	EXPECT_ANY_THROW(message_66::parse({0x66, 0x02, 0x00}));
}

TEST_F(Test_seatalk_message_66, parse)
{
	for (auto const & t : cases) {
		auto generic_message = message_66::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_66>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(t.a, m->get_alarm());
	}
}

TEST_F(Test_seatalk_message_66, write_default)
{
	const raw expected{0x66, 0x00, 0x00};
	message_66 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_66, set_alarm)
{
	for (auto const & t : cases) {
		message_66 m;
		m.set_alarm(t.a);
		const auto raw = m.get_data();
		EXPECT_EQ(t.data, raw);
	}
}

TEST_F(Test_seatalk_message_66, operator_and)
{
	const alarm a = static_cast<alarm>(0xff);

	EXPECT_EQ(alarm::apparent_angle_lo, a & alarm::apparent_angle_lo);
	EXPECT_EQ(alarm::apparent_angle_lo, a & alarm::apparent_angle_lo);
	EXPECT_EQ(alarm::apparent_angle_hi, a & alarm::apparent_angle_hi);
	EXPECT_EQ(alarm::apparent_speed_lo, a & alarm::apparent_speed_lo);
	EXPECT_EQ(alarm::apparent_speed_hi, a & alarm::apparent_speed_hi);
	EXPECT_EQ(alarm::true_angle_lo    , a & alarm::true_angle_lo    );
	EXPECT_EQ(alarm::true_angle_hi    , a & alarm::true_angle_hi    );
	EXPECT_EQ(alarm::true_speed_lo    , a & alarm::true_speed_lo    );
}
}
