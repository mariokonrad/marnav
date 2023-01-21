#include <marnav/seatalk/message_24.hpp>
#include <gtest/gtest.h>

namespace
{

using namespace marnav::seatalk;

class test_seatalk_message_24 : public ::testing::Test
{
};

TEST_F(test_seatalk_message_24, construction)
{
	message_24 m;
}

TEST_F(test_seatalk_message_24, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_24::parse({4, 0x00}));
	EXPECT_ANY_THROW(message_24::parse({6, 0x00}));
}

TEST_F(test_seatalk_message_24, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_24::parse({0x24, 0x01, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_24::parse({0x24, 0x03, 0x00, 0x00, 0x00}));
}

TEST_F(test_seatalk_message_24, parse)
{
	struct test_case {
		raw data;
		message_24::unit_type unit;
	};

	std::vector<test_case> cases{
		{{0x24, 0x02, 0x00, 0x00, 0x00}, message_24::unit_type::nautical_miles},
		{{0x24, 0x02, 0x00, 0x00, 0x00}, message_24::unit_type::knots},
		{{0x24, 0x02, 0x00, 0x00, 0x06}, message_24::unit_type::statute_miles},
		{{0x24, 0x02, 0x00, 0x00, 0x06}, message_24::unit_type::statute_miles_per_hour},
		{{0x24, 0x02, 0x00, 0x00, 0x86}, message_24::unit_type::kilometers},
		{{0x24, 0x02, 0x00, 0x00, 0x86}, message_24::unit_type::kilometers_per_hour},
	};

	for (auto const & t : cases) {
		auto generic_message = message_24::parse(t.data);
		EXPECT_TRUE(generic_message != nullptr);
		if (!generic_message)
			continue;
		auto m = message_cast<message_24>(generic_message);
		EXPECT_TRUE(m != nullptr);
		if (!m)
			continue;
		EXPECT_EQ(message_id::display_units_mileage_speed, m->type());
		EXPECT_EQ(t.unit, m->get_unit());
	}
}

TEST_F(test_seatalk_message_24, write_default)
{
	const raw expected{0x24, 0x02, 0x00, 0x00, 0x00};
	message_24 m;
	EXPECT_EQ(expected, m.get_data());
}

TEST_F(test_seatalk_message_24, write_unit)
{
	const raw expected{0x24, 0x02, 0x00, 0x00, 0x86};
	message_24 m;
	m.set_unit(message_24::unit_type::kilometers);

	EXPECT_EQ(expected, m.get_data());
}
}
