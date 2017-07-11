#include "message_21.hpp"

namespace marnav
{
namespace seatalk
{

message_21::message_21()
	: message(ID)
	, distance_(0)
{
}

std::unique_ptr<message> message_21::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_21>();
	message_21 & msg = static_cast<message_21 &>(*result);

	msg.distance_ = 0;
	msg.distance_ += data[2];
	msg.distance_ <<= 8;
	msg.distance_ += data[3];
	msg.distance_ <<= 4;
	msg.distance_ += data[4] & 0x0f;

	return result;
}

raw message_21::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x02, static_cast<uint8_t>((distance_ >> 12) & 0xff),
		static_cast<uint8_t>((distance_ >> 4) & 0xff),
		static_cast<uint8_t>((distance_ >> 0) & 0x0f)};
}
}
}
