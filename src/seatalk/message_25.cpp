#include "message_25.hpp"

namespace seatalk
{

message_25::message_25()
	: message(ID)
	, total(0)
	, trip(0)
{
}

std::unique_ptr<message> message_25::parse(const raw& data) throw(std::invalid_argument)
{
	if (data.size() != 7)
		throw std::invalid_argument{"invalid number of bytes in message_25::parse"};
	if ((data[1] & 0x0f) != 0x04)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_25>();
	message_25& msg = static_cast<message_25&>(*result);

	// 25  Z4  XX  YY  UU  VV AW
	// raw  1  2   3   4   5  6

    // total= (XX+YY*256+Z*65536)/ 10 [max=104857.5] nautical miles
	// (the factor for Z in the description from Thomas Knauf is wrong)
	msg.total = 0;
	msg.total += 65536 * ((data[1] & 0xf0) >> 4);
	msg.total += 256 * data[3];
	msg.total += data[2];

    // trip = (UU+VV*256+W*65536)/100 [max=10485.75] nautical miles
	msg.trip = 0;
	msg.trip += 65536 * (data[6] & 0xf);
	msg.trip += 256 * data[5];
	msg.trip += data[4];

	return result;
}

raw message_25::get_data() const
{
	return raw{
		static_cast<uint8_t>(ID), 0x04 | static_cast<uint8_t>(((total >> 16) & 0x0f) << 4),
		static_cast<uint8_t>((total >> 8) & 0xff), // YY
		static_cast<uint8_t>((total >> 0) & 0xff), // XX
		static_cast<uint8_t>((trip >> 0) & 0xff), // UU
		static_cast<uint8_t>((trip >> 8) & 0xff), // VV
		static_cast<uint8_t>((trip >> 16) & 0x0f) // AW
	};
}

}
