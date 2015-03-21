#include "message_21.hpp"

namespace seatalk
{

message_21::message_21()
	: message(ID)
	, distance(0)
{
}

std::unique_ptr<message> message_21::parse(const raw& data) throw(std::invalid_argument)
{
	if (data.size() != 5)
		throw std::invalid_argument{"invalid number of bytes in message_21::parse"};
	if (data[1] != 0x02)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_21>();
	message_21& msg = static_cast<message_21&>(*result);

	msg.distance = 0;
	msg.distance += data[2];
	msg.distance <<= 8;
	msg.distance += data[3];
	msg.distance <<= 4;
	msg.distance += data[4] & 0x0f;

	return result;
}

raw message_21::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x02, static_cast<uint8_t>((distance >> 12) & 0xff),
			   static_cast<uint8_t>((distance >> 4) & 0xff),
			   static_cast<uint8_t>((distance >> 0) & 0x0f)};
}

}
