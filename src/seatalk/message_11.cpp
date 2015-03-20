#include "message_11.hpp"

namespace seatalk
{

message_11::message_11()
	: message(ID)
	, unit(seatalk::unit::KNOT)
	, speed(0)
{
}

std::unique_ptr<message> message_11::parse(const raw& data) throw(std::invalid_argument)
{
	if (data.size() != 4)
		throw std::invalid_argument{"invalid number of bytes in message_11::parse"};
	if (data[1] != 0x01)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_11>();
	message_11& msg = static_cast<message_11&>(*result);

	msg.speed = 0;
	msg.speed += data[2] & 0x7f;
	msg.speed *= 10;
	msg.speed += data[3] & 0x0f;

	msg.unit = (data[2] & 0x80) ? unit::MPS : unit::KNOT;

	return result;
}

raw message_11::get_data() const
{
	uint8_t v0 = static_cast<uint8_t>((speed >> 8) & 0x7f) | (unit == unit::MPS) ? 0x80 : 0x00;
	uint8_t v1 = static_cast<uint8_t>((speed >> 0) & 0x0f);

	return raw{static_cast<uint8_t>(ID), 0x01, v0, v1};
}

}
