#include "message_10.hpp"

namespace marnav
{
namespace seatalk
{

message_10::message_10()
	: message(ID)
	, angle_(0)
{
}

std::unique_ptr<message> message_10::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_10>();
	message_10 & msg = static_cast<message_10 &>(*result);

	msg.angle_ = 0;
	msg.angle_ += data[2];
	msg.angle_ <<= 8;
	msg.angle_ += data[3];

	msg.angle_ *= 10;
	msg.angle_ /= 2;

	return result;
}

raw message_10::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x01, static_cast<uint8_t>((angle_ >> 0) & 0xff),
		static_cast<uint8_t>((angle_ >> 8) & 0xff)};
}
}
}
