#include <marnav/seatalk/message_25.hpp>

namespace marnav::seatalk
{

message_25::message_25()
	: message(ID)
{
}

std::unique_ptr<message> message_25::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = std::make_unique<message_25>();
	auto & msg = static_cast<message_25 &>(*result);

	// 25  Z4  XX  YY  UU  VV AW
	// raw  1  2   3   4   5  6

	// total= (XX+YY*256+Z*65536)/ 10 [max=104857.5] nautical miles
	// (the factor for Z in the description from Thomas Knauf is wrong)
	msg.total_ = 0;
	msg.total_ += 65536 * ((data[1] & 0xf0) >> 4);
	msg.total_ += 256 * data[3];
	msg.total_ += data[2];

	// trip = (UU+VV*256+W*65536)/100 [max=10485.75] nautical miles
	msg.trip_ = 0;
	msg.trip_ += 65536 * (data[6] & 0xf);
	msg.trip_ += 256 * data[5];
	msg.trip_ += data[4];

	return result;
}

raw message_25::get_data() const
{
	uint8_t attr = 0x04;
	attr |= static_cast<uint8_t>(((total_ >> 16) & 0x0f) << 4);
	return raw{
		static_cast<uint8_t>(ID), attr,
		static_cast<uint8_t>((total_ >> 8) & 0xff), // YY
		static_cast<uint8_t>((total_ >> 0) & 0xff), // XX
		static_cast<uint8_t>((trip_ >> 0) & 0xff), // UU
		static_cast<uint8_t>((trip_ >> 8) & 0xff), // VV
		static_cast<uint8_t>((trip_ >> 16) & 0x0f) // AW
	};
}
}
