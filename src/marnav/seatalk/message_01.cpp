#include "message_01.hpp"

namespace marnav
{
namespace seatalk
{

message_01::message_01()
	: message(ID)
	, equipment_id{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}}
{
}

std::unique_ptr<message> message_01::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_01>();
	message_01 & msg = static_cast<message_01 &>(*result);

	for (auto i = 0; i < 6; ++i) {
		msg.equipment_id[i] = data[i + 2];
	}

	return result;
}

raw message_01::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x05, equipment_id[0], equipment_id[1],
		equipment_id[2], equipment_id[3], equipment_id[4], equipment_id[5]};
}
}
}
