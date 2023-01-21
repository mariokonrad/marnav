#include <marnav/seatalk/message_30.hpp>

namespace marnav::seatalk
{

message_30::message_30()
	: message(ID)
{
}

std::unique_ptr<message> message_30::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = std::make_unique<message_30>();
	auto & msg = static_cast<message_30 &>(*result);

	msg.value_ = static_cast<intensity>(data[2] & 0x0f);

	return result;
}

raw message_30::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x00, static_cast<uint8_t>(value_)};
}
}
