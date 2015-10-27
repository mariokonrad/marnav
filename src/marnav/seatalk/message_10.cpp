#include "message_10.hpp"

namespace marnav
{
namespace seatalk
{

message_10::message_10()
	: message(ID)
	, angle(0)
{
}

std::unique_ptr<message> message_10::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_10>();
	message_10 & msg = static_cast<message_10 &>(*result);

	msg.angle = 0;
	msg.angle += data[2];
	msg.angle <<= 8;
	msg.angle += data[3];

	msg.angle *= 10;
	msg.angle /= 2;

	return result;
}

raw message_10::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x01, static_cast<uint8_t>((angle >> 0) & 0xff),
		static_cast<uint8_t>((angle >> 8) & 0xff)};
}
}
}
