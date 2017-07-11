#include "message_11.hpp"

namespace marnav
{
namespace seatalk
{
message_11::message_11()
	: message(ID)
	, unit_(seatalk::unit::KNOT)
	, speed_(0)
{
}

std::unique_ptr<message> message_11::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_11>();
	message_11 & msg = static_cast<message_11 &>(*result);

	msg.speed_ = 0;
	msg.speed_ += data[2] & 0x7f;
	msg.speed_ *= 10;
	msg.speed_ += data[3] & 0x0f;

	msg.unit_ = (data[2] & 0x80) ? unit::MPS : unit::KNOT;

	return result;
}

raw message_11::get_data() const
{
	uint8_t v0
		= static_cast<uint8_t>((speed_ >> 8) & 0x7f) | ((unit_ == unit::MPS) ? 0x80 : 0x00);
	uint8_t v1 = static_cast<uint8_t>((speed_ >> 0) & 0x0f);

	return raw{static_cast<uint8_t>(ID), 0x01, v0, v1};
}
}
}
