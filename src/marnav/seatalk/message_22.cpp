#include "message_22.hpp"

namespace marnav
{
namespace seatalk
{

message_22::message_22()
	: message(ID)
	, distance(0)
{
}

std::unique_ptr<message> message_22::parse(const raw & data) throw(std::invalid_argument)
{
	if (data.size() != 5)
		throw std::invalid_argument{"invalid number of bytes in message_22::parse"};
	if (data[1] != 0x02)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_22>();
	message_22 & msg = static_cast<message_22 &>(*result);

	msg.distance = 0;
	msg.distance += data[2];
	msg.distance <<= 8;
	msg.distance += data[3];

	return result;
}

raw message_22::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x02, static_cast<uint8_t>((distance >> 8) & 0xff),
		static_cast<uint8_t>((distance >> 0) & 0xff), 0x00};
}
}
}
