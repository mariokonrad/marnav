#include <gtest/gtest.h>
#include <seatalk/message_23.hpp>

namespace
{
class Test_seatalk_message_23 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_23, construction)
{
	seatalk::message_23 m;
}

TEST_F(Test_seatalk_message_23, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_23::parse({3, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_23::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_23, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_23::parse({0x23, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_23::parse({0x23, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_23, parse)
{
	struct test_case
	{
		seatalk::raw data;
		bool sensor_defective;
		uint8_t temperature_celsius;
		uint8_t temperature_fahrenheit;
	};

	std::vector<test_case> cases{
		{{0x23, 0x01, 0x00, 0x00}, false, 0, 0},
		{{0x23, 0x41, 0x00, 0x00}, true, 0, 0},
		{{0x23, 0x01, 0x01, 0x00}, false, 1, 0},
		{{0x23, 0x01, 0x00, 0x01}, false, 0, 1},
		{{0x23, 0x01, 0x64, 0x00}, false, 100, 0},
		{{0x23, 0x01, 0x00, 0x64}, false, 0, 100},
	};

	for (auto const& t : cases) {
		auto generic_message = seatalk::message_23::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = seatalk::message_cast<seatalk::message_23>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(seatalk::message_id::water_temperature_1, m->type());
		EXPECT_EQ(t.temperature_celsius, m->get_celsius());
		EXPECT_EQ(t.temperature_fahrenheit, m->get_fahrenheit());
	}
}

TEST_F(Test_seatalk_message_23, write_default)
{
	const seatalk::raw expected{0x23, 0x01, 0x00, 0x00};
	seatalk::message_23 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_23, write_sensor_defectie)
{
	const seatalk::raw expected{0x23, 0x41, 0x00, 0x00};
	seatalk::message_23 m;
	m.set_sensor_defective(true);

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_23, write_celcius)
{
	const seatalk::raw expected{0x23, 0x01, 0x01, 0x00};
	seatalk::message_23 m;
	m.set_celsius(1);

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_23, write_fahrenheit)
{
	const seatalk::raw expected{0x23, 0x01, 0x00, 0x01};
	seatalk::message_23 m;
	m.set_fahrenheit(1);

	EXPECT_EQ(expected, m.get_data());
}

}
