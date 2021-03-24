#include <marnav/seatalk/message_01.hpp>
#include <gtest/gtest.h>

namespace
{
using namespace marnav;
using namespace marnav::seatalk;

class Test_seatalk_message_01 : public ::testing::Test
{
};

TEST_F(Test_seatalk_message_01, construction)
{
	message_01 m;
}

TEST_F(Test_seatalk_message_01, parse_invalid_data_size)
{
	EXPECT_ANY_THROW(message_01::parse({7, 0x00}));
	EXPECT_ANY_THROW(message_01::parse({9, 0x00}));
}

TEST_F(Test_seatalk_message_01, parse_invalid_length)
{
	EXPECT_ANY_THROW(message_01::parse({0x01, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
	EXPECT_ANY_THROW(message_01::parse({0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
}

TEST_F(Test_seatalk_message_01, parse)
{
	struct test_case {
		seatalk::raw data;
		equipment_id id;
	};

	std::vector<test_case> cases{
		{{0x01, 0x05, 0x00, 0x00, 0x00, 0x60, 0x01, 0x00}, message_01::course_computer_400g},
		{{0x01, 0x05, 0x04, 0xBA, 0x20, 0x28, 0x01, 0x00}, message_01::st60_tridata},
		{{0x01, 0x05, 0x70, 0x99, 0x10, 0x28, 0x01, 0x00}, message_01::st60_log},
		{{0x01, 0x05, 0xF3, 0x18, 0x00, 0x26, 0x0F, 0x06}, message_01::st80_masterview},
		{{0x01, 0x05, 0xFA, 0x03, 0x00, 0x30, 0x07, 0x03}, message_01::st80_maxi_display},
		{{0x01, 0x05, 0xFF, 0xFF, 0xFF, 0xD0, 0x00, 0x00},
			message_01::smart_controller_remote_control_handset},
	};

	for (auto const & t : cases) {
		auto generic_message = message_01::parse(t.data);
		ASSERT_TRUE(generic_message != nullptr);
		auto m = message_cast<message_01>(generic_message);
		ASSERT_TRUE(m != nullptr);
		EXPECT_EQ(message_id::equipment_id, m->type());
		EXPECT_EQ(t.id, m->get_equipment_id());
	}
}

TEST_F(Test_seatalk_message_01, write_default)
{
	const seatalk::raw expected{0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	message_01 m;

	EXPECT_EQ(expected, m.get_data());
}

TEST_F(Test_seatalk_message_01, write)
{
	const seatalk::raw expected{0x01, 0x05, 0x00, 0x00, 0x00, 0x60, 0x01, 0x00};
	message_01 m;
	m.set_equipment_id(message_01::course_computer_400g);

	EXPECT_EQ(expected, m.get_data());
}
}
