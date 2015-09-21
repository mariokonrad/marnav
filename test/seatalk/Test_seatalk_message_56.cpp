#include <gtest/gtest.h>
#include <marnav/seatalk/message_56.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_56 : public ::testing::Test
{
public:
	struct test_case {
		raw data;
		uint8_t y;
		uint8_t m;
		uint8_t d;
	};
};

TEST_F(Test_seatalk_message_56, construction) { EXPECT_NO_THROW(message_56 m); }

TEST_F(Test_seatalk_message_56, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_56::parse({3, 0x00}));
	EXPECT_ANY_THROW(message_56::parse({5, 0x00}));
}

TEST_F(Test_seatalk_message_56, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_56::parse({0x56, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_56::parse({0x56, 0x02, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_56, parse)
{
	const std::vector<test_case> cases{
		{{0x56, 0x01, 0x00, 0x00}, 0, 0, 0},
		{{0x56, 0x01, 0x00, 0x01}, 1, 0, 0},
		{{0x56, 0x01, 0x01, 0x00}, 0, 0, 1},
		{{0x56, 0x11, 0x00, 0x00}, 0, 1, 0},
	};

	for (auto const & t : cases) {
		auto generic_message = message_56::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_56>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(t.y, m->get_year());
		EXPECT_EQ(t.m, m->get_month());
		EXPECT_EQ(t.d, m->get_day());
	}
}

TEST_F(Test_seatalk_message_56, write_default)
{
	const raw expected{0x56, 0x01, 0x00, 0x00};
	message_56 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_56, set_date)
{
	const std::vector<test_case> cases{
		{{0x56, 0x01, 0x00, 0x00}, 0, 0, 0},
		{{0x56, 0x01, 0x00, 0x01}, 1, 0, 0},
		{{0x56, 0x01, 0x01, 0x00}, 0, 0, 1},
		{{0x56, 0x11, 0x00, 0x00}, 0, 1, 0},
	};

	for (auto const & t : cases) {
		message_56 m;
		m.set_date(t.y, t.m, t.d);
		const auto raw = m.get_data();
		EXPECT_EQ(t.data, raw);
	}
}
}
