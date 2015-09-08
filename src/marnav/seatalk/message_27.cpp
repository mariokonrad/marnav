#include "message_27.hpp"

namespace marnav
{
namespace seatalk
{

message_27::message_27()
	: message(ID)
	, temperature(0)
{
}

std::unique_ptr<message> message_27::parse(const raw & data)
{
	if (data.size() != 4)
		throw std::invalid_argument{"invalid number of bytes in message_27::parse"};
	if (data[1] != 0x01)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_27>();
	message_27 & msg = static_cast<message_27 &>(*result);

	uint16_t value = 0;
	value += data[2];
	value <<= 8;
	value += data[3];

	msg.temperature = value;
	msg.temperature -= 100;

	return result;
}

raw message_27::get_data() const
{
	uint16_t value = (temperature + 100) & 0xffff;

	return raw{static_cast<uint8_t>(ID), 0x01, static_cast<uint8_t>((value >> 8) & 0xff),
		static_cast<uint8_t>((value >> 0) & 0xff)};
}
}
}
