#include "message_56.hpp"

namespace marnav
{
namespace seatalk
{

message_56::message_56()
	: message(ID)
	, year(0)
	, month(0)
	, day(0)
{
}

std::unique_ptr<message> message_56::parse(const raw & data)
{
	if (data.size() != 4)
		throw std::invalid_argument{"invalid number of bytes in message_56::parse"};
	if ((data[1] & 0x0f) != 0x01)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_56>();
	message_56 & msg = static_cast<message_56 &>(*result);

	//  56 M1 DD YY
	// raw  1  2  3

	msg.year = data[3];
	msg.month = (data[1] >> 4) & 0x0f;
	msg.day = data[2];

	return result;
}

raw message_56::get_data() const
{
	return raw{static_cast<uint8_t>(ID), static_cast<uint8_t>(0x01 | ((month << 4) & 0xf0)),
		day, year};
}

/// @todo Test rages of parameters
void message_56::set_date(uint8_t y, uint8_t m, uint8_t d) noexcept
{
	year = y;
	month = m;
	day = d;
}
}
}
