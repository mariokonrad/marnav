#include "message_20.hpp"

namespace marnav
{
namespace seatalk
{

message_20::message_20()
	: message(ID)
	, speed(0)
{
}

std::unique_ptr<message> message_20::parse(const raw & data) throw(std::invalid_argument)
{
	if (data.size() != 4)
		throw std::invalid_argument{"invalid number of bytes in message_20::parse"};
	if (data[1] != 0x01)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_20>();
	message_20 & msg = static_cast<message_20 &>(*result);

	msg.speed = 0;
	msg.speed += data[2];
	msg.speed <<= 8;
	msg.speed += data[3];

	return result;
}

raw message_20::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x01, static_cast<uint8_t>((speed >> 8) & 0xff),
		static_cast<uint8_t>((speed >> 0) & 0xff)};
}
}
}
