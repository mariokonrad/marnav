#include "message_30.hpp"

namespace marnav
{
namespace seatalk
{

message_30::message_30()
	: message(ID)
	, value(intensity::L0)
{
}

std::unique_ptr<message> message_30::parse(const raw & data)
{
	if (data.size() != 3)
		throw std::invalid_argument{"invalid number of bytes in message_30::parse"};
	if (data[1] != 0x00)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_30>();
	message_30 & msg = static_cast<message_30 &>(*result);

	msg.value = static_cast<intensity>(data[2] & 0x0f);

	return result;
}

raw message_30::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x00, static_cast<uint8_t>(value)};
}
}
}
