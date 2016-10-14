#include <gtest/gtest.h>
#include <marnav/seatalk/message_30.hpp>

namespace
{

using namespace marnav::seatalk;

class Test_seatalk_message_30 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_30, construction)
{
	message_30 m;
}

TEST_F(Test_seatalk_message_30, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_30::parse({2, 0x00}));
	EXPECT_ANY_THROW(message_30::parse({4, 0x00}));
}

TEST_F(Test_seatalk_message_30, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_30::parse({0x30, 0x01, 0x00}));
	EXPECT_ANY_THROW(message_30::parse({0x30, 0x02, 0x00}));
}

TEST_F(Test_seatalk_message_30, parse)
{
	struct test_case {
		raw data;
		message_30::intensity value;
	};

	std::vector<test_case> cases{
		{{0x30, 0x00, 0x00}, message_30::intensity::L0},
		{{0x30, 0x00, 0x04}, message_30::intensity::L1},
		{{0x30, 0x00, 0x08}, message_30::intensity::L2},
		{{0x30, 0x00, 0x0c}, message_30::intensity::L3},
	};

	for (auto const & t : cases) {
		auto generic_message = message_30::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_30>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(message_id::set_lamp_intensity, m->type());
		EXPECT_EQ(t.value, m->get_intensity());
	}
}

TEST_F(Test_seatalk_message_30, write_default)
{
	const raw expected{0x30, 0x00, 0x00};
	message_30 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_30, set_intensity)
{
	{
		const raw expected{0x30, 0x00, 0x00};
		message_30 m;
		m.set_intensity(message_30::intensity::L0);
		EXPECT_EQ(expected, m.get_data());
	}
	{
		const raw expected{0x30, 0x00, 0x04};
		message_30 m;
		m.set_intensity(message_30::intensity::L1);
		EXPECT_EQ(expected, m.get_data());
	}
	{
		const raw expected{0x30, 0x00, 0x08};
		message_30 m;
		m.set_intensity(message_30::intensity::L2);
		EXPECT_EQ(expected, m.get_data());
	}
	{
		const raw expected{0x30, 0x00, 0x0c};
		message_30 m;
		m.set_intensity(message_30::intensity::L3);
		EXPECT_EQ(expected, m.get_data());
	}
}
}
