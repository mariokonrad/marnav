#include <marnav/seatalk/message_87.hpp>

namespace marnav::seatalk
{
message_87::message_87()
	: message(ID)
{
}

std::unique_ptr<message> message_87::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = std::make_unique<message_87>();
	auto & msg = static_cast<message_87 &>(*result);

	//  87 00 0X
	// raw  1  2

	msg.level_ = static_cast<response_level>(data[2] & 0x0f);

	return result;
}

raw message_87::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x00, static_cast<uint8_t>(level_)};
}
}
