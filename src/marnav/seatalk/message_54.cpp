#include "message_54.hpp"
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_54::message_54()
	: message(ID)
	, hour_(0)
	, minute_(0)
	, second_(0)
{
}

std::unique_ptr<message> message_54::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_54>();
	message_54 & msg = static_cast<message_54 &>(*result);

	//  54 T1 RS HH
	// raw  1  2  3

	msg.hour_ = data[3];
	msg.minute_ = (data[2] & 0xfc) / 4;
	msg.second_ = (((data[2] << 4) & 0xf0) | ((data[1] >> 4) & 0x0f)) & 0x3f;

	return result;
}

raw message_54::get_data() const
{
	uint8_t rs = 0;
	uint8_t t = 0;

	rs += (minute_ * 4) & 0xfc;
	rs += (second_ >> 4) & 0x03;

	t += second_ & 0x0f;
	t <<= 4;

	return raw{static_cast<uint8_t>(ID), static_cast<uint8_t>(0x01 | t), rs, hour_};
}

/// @todo Test rages of parameters
void message_54::set_time(uint8_t h, uint8_t m, uint8_t s) noexcept
{
	hour_ = h;
	minute_ = m;
	second_ = s;
}
}
}
