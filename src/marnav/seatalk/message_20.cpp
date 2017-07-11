#include "message_20.hpp"

namespace marnav
{
namespace seatalk
{

message_20::message_20()
	: message(ID)
	, speed_(0)
{
}

std::unique_ptr<message> message_20::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_20>();
	message_20 & msg = static_cast<message_20 &>(*result);

	msg.speed_ = 0;
	msg.speed_ += data[2];
	msg.speed_ <<= 8;
	msg.speed_ += data[3];

	return result;
}

raw message_20::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x01, static_cast<uint8_t>((speed_ >> 8) & 0xff),
		static_cast<uint8_t>((speed_ >> 0) & 0xff)};
}
}
}
