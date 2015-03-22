#include <gtest/gtest.h>
#include <seatalk/message_27.hpp>

namespace
{
class Test_seatalk_message_27 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_27, construction)
{
	seatalk::message_27 m;
}

TEST_F(Test_seatalk_message_27, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(seatalk::message_27::parse({3, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_27::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_27, parse_invalid_length)
{
	EXPECT_ANY_THROW(seatalk::message_27::parse({0x27, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(seatalk::message_27::parse({0x27, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_27, parse)
{
	struct test_case
	{
		seatalk::raw data;
		int32_t temperature;
	};

	std::vector<test_case> cases{
		{{0x27, 0x01, 0x00, 0x00}, -100}, // -10.0 degree celsius
		{{0x27, 0x01, 0x10, 0x00}, 3996}, // 399.6 degree celsius
		{{0x27, 0x01, 0x00, 0x10}, -84}, //  -8.4 degree celsius
		{{0x27, 0x01, 0x10, 0x10}, 4012}, // 401.2 degree celsius
		{{0x27, 0x01, 0x00, 0x64}, 0}, //   0.0 degree celsius
		{{0x27, 0x01, 0x00, 0x65}, 1}, //   1.0 degree celsius
		{{0x27, 0x01, 0x00, 0x63}, -1}, //  -1.0 degree celsius
	};

	for (auto const& t : cases) {
		auto generic_message = seatalk::message_27::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = seatalk::message_cast<seatalk::message_27>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(seatalk::message_id::water_temperature_2, m->type());
		EXPECT_EQ(t.temperature, m->get_temperature());
	}
}

TEST_F(Test_seatalk_message_27, write_default)
{
	const seatalk::raw expected{0x27, 0x01, 0x00, 0x64};
	seatalk::message_27 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_27, write_distance)
{
	const seatalk::raw expected{0x27, 0x01, 0x00, 0x01};
	seatalk::message_27 m;
	m.set_temperature(-99);

	EXPECT_EQ(expected, m.get_data());
}

}
