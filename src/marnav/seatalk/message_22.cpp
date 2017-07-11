#include "message_22.hpp"

namespace marnav
{
namespace seatalk
{

message_22::message_22()
	: message(ID)
	, distance_(0)
{
}

std::unique_ptr<message> message_22::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_22>();
	message_22 & msg = static_cast<message_22 &>(*result);

	msg.distance_ = 0;
	msg.distance_ += data[2];
	msg.distance_ <<= 8;
	msg.distance_ += data[3];

	return result;
}

raw message_22::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x02, static_cast<uint8_t>((distance_ >> 8) & 0xff),
		static_cast<uint8_t>((distance_ >> 0) & 0xff), 0x00};
}
}
}
