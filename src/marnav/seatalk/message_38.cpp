#include "message_38.hpp"

namespace marnav
{
namespace seatalk
{

message_38::message_38()
	: message(ID)
{
}

std::unique_ptr<message> message_38::parse(const raw & data)
{
	if (data.size() != 4)
		throw std::invalid_argument{"invalid number of bytes in message_38::parse"};
	if ((data[1] & 0x0f) != 0x01)
		throw std::invalid_argument{"invalid size specified in message"};

	return utils::make_unique<message_38>();
}

raw message_38::get_data() const { return raw{static_cast<uint8_t>(ID), 0x01, 0x00, 0x00}; }
}
}
