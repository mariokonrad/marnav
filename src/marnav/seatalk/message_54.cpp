#include "message_54.hpp"
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_54::message_54()
	: message(ID)
	, hour(0)
	, minute(0)
	, second(0)
{
}

std::unique_ptr<message> message_54::parse(const raw & data)
{
	if (data.size() != 4)
		throw std::invalid_argument{"invalid number of bytes in message_54::parse"};
	if ((data[1] & 0x0f) != 0x01)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_54>();
	message_54 & msg = static_cast<message_54 &>(*result);

	//  54 T1 RS HH
	// raw  1  2  3

	msg.hour = data[3];
	msg.minute = (data[2] & 0xfc) / 4;
	msg.second = (((data[2] << 4) & 0xf0) | ((data[1] >> 4) & 0x0f)) & 0x3f;

	return result;
}

raw message_54::get_data() const
{
	// TODO

	return raw{static_cast<uint8_t>(ID), 0x01, 0x00, hour};
}

/// @todo Test rages of parameters
void message_54::set_time(uint8_t h, uint8_t m, uint8_t s) noexcept
{
	hour = h;
	minute = m;
	second = s;
}
}
}
