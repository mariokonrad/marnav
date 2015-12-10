#include "message_6c.hpp"

namespace marnav
{
namespace seatalk
{
constexpr equipment_id message_6c::st60_tridata;
constexpr equipment_id message_6c::st60_log;
constexpr equipment_id message_6c::st80_masterview;

message_6c::message_6c()
	: message(ID)
	, id(equipment_invalid)
{
}

std::unique_ptr<message> message_6c::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_6c>();
	message_6c & msg = static_cast<message_6c &>(*result);

	for (auto i = 0; i < 6; ++i)
		msg.id[i] = data[i + 2];

	return result;
}

raw message_6c::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x05, id[0], id[1], id[2], id[3], id[4], id[5]};
}
}
}
