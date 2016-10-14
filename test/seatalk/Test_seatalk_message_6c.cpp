#include <gtest/gtest.h>
#include <marnav/seatalk/message_6c.hpp>

namespace
{
using namespace marnav;
using namespace marnav::seatalk;

class Test_seatalk_message_6c : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_6c, construction)
{
	message_6c m;
}

TEST_F(Test_seatalk_message_6c, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_6c::parse({7, 0x00}));
	EXPECT_ANY_THROW(message_6c::parse({9, 0x00}));
}

TEST_F(Test_seatalk_message_6c, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_6c::parse({0x6c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_6c::parse({0x6c, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_6c, parse)
{
	struct test_case {
		seatalk::raw data;
		equipment_id id;
	};

	std::vector<test_case> cases{
		{{0x6C, 0x05, 0x04, 0xBA, 0x20, 0x28, 0x2D, 0x2D}, message_6c::st60_tridata},
		{{0x6C, 0x05, 0x05, 0x70, 0x99, 0x10, 0x28, 0x2D}, message_6c::st60_log},
		{{0x6C, 0x05, 0xF3, 0x18, 0x00, 0x26, 0x2D, 0x2D}, message_6c::st80_masterview},
	};

	for (auto const & t : cases) {
		auto generic_message = message_6c::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = message_cast<message_6c>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(message_id::equipment_id_2, m->type());
		EXPECT_EQ(t.id, m->get_equipment_id());
	}
}

TEST_F(Test_seatalk_message_6c, write_default)
{
	const raw expected{0x6c, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	message_6c m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_6c, write)
{
	const raw expected{0x6c, 0x05, 0x04, 0xBA, 0x20, 0x28, 0x2D, 0x2D};
	message_6c m;
	m.set_equipment_id(message_6c::st60_tridata);

	EXPECT_EQ(expected, m.get_data());
}
}
