#include "message_05.hpp"

namespace marnav
{
namespace seatalk
{

namespace
{
static uint8_t conv(message_05::side_id side)
{
	switch (side) {
		case message_05::side_id::undefined:
			return 0x00u;
		case message_05::side_id::starboard:
			return 0x01u;
		case message_05::side_id::port:
			return 0x02u;
	}
	return 0x00u;
}

static message_05::side_id conv(uint8_t t)
{
	switch (t & 0x0fu) {
		case 0x00u:
			return message_05::side_id::undefined;
		case 0x01u:
			return message_05::side_id::starboard;
		case 0x02u:
			return message_05::side_id::port;
		default:
			break;
	}
	return message_05::side_id::undefined;
}
}

message_05::message_05()
	: message(ID)
	, side(side_id::undefined)
	, rpm(0)
	, percent_pitch(0)
{
}

std::unique_ptr<message> message_05::parse(const raw & data) throw(std::invalid_argument)
{
	if (data.size() != 6)
		throw std::invalid_argument{"invalid number of bytes in message_05::parse"};
	if (data[1] != 0x03)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_05>();
	message_05 & msg = static_cast<message_05 &>(*result);

	msg.side = conv(data[2]);

	msg.rpm = 0;
	msg.rpm += data[3];
	msg.rpm <<= 8;
	msg.rpm += data[4];

	msg.percent_pitch = static_cast<int8_t>(data[5]);

	return result;
}

raw message_05::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x03, conv(side), static_cast<uint8_t>((rpm >> 8) & 0xff),
		static_cast<uint8_t>(rpm & 0xff), static_cast<uint8_t>(percent_pitch)};
}
}
}
