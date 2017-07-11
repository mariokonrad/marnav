#include "message_01.hpp"

namespace marnav
{
namespace seatalk
{
constexpr equipment_id message_01::course_computer_400g;
constexpr equipment_id message_01::st60_tridata;
constexpr equipment_id message_01::st60_log;
constexpr equipment_id message_01::st80_masterview;
constexpr equipment_id message_01::st80_maxi_display;
constexpr equipment_id message_01::smart_controller_remote_control_handset;

message_01::message_01()
	: message(ID)
	, id_(equipment_invalid)
{
}

std::unique_ptr<message> message_01::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_01>();
	message_01 & msg = static_cast<message_01 &>(*result);

	for (auto i = 0; i < 6; ++i)
		msg.id_[i] = data[i + 2];

	return result;
}

raw message_01::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x05, id_[0], id_[1], id_[2], id_[3], id_[4], id_[5]};
}
}
}
