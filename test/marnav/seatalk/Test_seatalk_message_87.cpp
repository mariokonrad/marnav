#include <marnav/seatalk/message_87.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav::seatalk;

class test_seatalk_message_87 : public ::testing::Test
{
public:
	struct test_case {
		raw data;
		message_87::response_level level;
	};

	const std::vector<test_case> cases{
		{{0x86, 0x00, 0x00}, message_87::response_level::invalid},
		{{0x86, 0x00, 0x01}, message_87::response_level::automatic},
		{{0x86, 0x00, 0x02}, message_87::response_level::minimum},
	};
};

TEST_F(test_seatalk_message_87, construction)
{
	EXPECT_NO_THROW(message_87 m);
}

TEST_F(test_seatalk_message_87, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_87::parse({1, 0x00}));
}

TEST_F(test_seatalk_message_87, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_87::parse({0x87, 0x01, 0x00}));
}

TEST_F(test_seatalk_message_87, parse)
{
	for (auto const & t : cases) {
		auto generic_message = message_87::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_87>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(t.level, m->get_level());
	}
}

TEST_F(test_seatalk_message_87, write_default)
{
	const raw expected{0x87, 0x00, 0x01};
	message_87 m;

	EXPECT_EQ(expected, m.get_data());
}
}
