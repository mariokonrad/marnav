#include <gtest/gtest.h>
#include <marnav/seatalk/message_53.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_53 : public ::testing::Test
{
public:
	struct test_case {
		raw data;
		double cog;
	};

	const std::vector<test_case> cases{
		{{0x53, 0x00, 0x00}, 0.0}, {{0x53, 0x00, 0x01}, 2.0}, {{0x53, 0x00, 0x02}, 4.0},
		{{0x53, 0x00, 0x04}, 8.0}, {{0x53, 0x00, 0x08}, 16.0}, {{0x53, 0x00, 0x10}, 32.0},
		{{0x53, 0x00, 0x20}, 64.0}, {{0x53, 0x10, 0x00}, 90.0}, {{0x53, 0x20, 0x00}, 180.0},
		{{0x53, 0x30, 0x00}, 270.0}, {{0x53, 0x40, 0x00}, 0.5}, {{0x53, 0x80, 0x00}, 1.0},
		{{0x53, 0xc0, 0x00}, 1.5},
	};
};

TEST_F(Test_seatalk_message_53, construction)
{
	EXPECT_NO_THROW(message_53 m);
}

TEST_F(Test_seatalk_message_53, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_53::parse({2, 0x00}));
	EXPECT_ANY_THROW(message_53::parse({4, 0x00}));
}

TEST_F(Test_seatalk_message_53, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_53::parse({0x53, 0x01, 0x00}));
	EXPECT_ANY_THROW(message_53::parse({0x53, 0x02, 0x00}));
}

TEST_F(Test_seatalk_message_53, parse)
{
	for (auto const & t : cases) {
		auto generic_message = message_53::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_53>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
	}
}

TEST_F(Test_seatalk_message_53, write_default)
{
	const raw expected{0x53, 0x00, 0x00};
	message_53 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_53, set_cog)
{
	for (auto const & t : cases) {
		message_53 m;
		m.set_cog(t.cog);
		const auto raw = m.get_data();
		EXPECT_EQ(t.data, raw) << "cog=" << t.cog;
	}
}
}
