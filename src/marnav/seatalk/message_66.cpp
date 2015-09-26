#include "message_66.hpp"

namespace marnav
{
namespace seatalk
{

message_66::message_66()
	: message(ID)
	, value(alarm::no_alarm)
{
}

std::unique_ptr<message> message_66::parse(const raw & data)
{
	if (data.size() != 3)
		throw std::invalid_argument{"invalid number of bytes in message_66::parse"};
	if ((data[1] & 0x0f) != 0x00)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_66>();
	message_66 & msg = static_cast<message_66 &>(*result);

	//  66 00 XX
	// raw  1  2

	msg.value = static_cast<alarm>(data[2]);

	return result;
}

raw message_66::get_data() const { return raw{static_cast<uint8_t>(ID), 0x00, value}; }

message_66::alarm operator|(message_66::alarm a, message_66::alarm b) noexcept
{
	const uint8_t ta = static_cast<uint8_t>(a);
	const uint8_t tb = static_cast<uint8_t>(b);
	return static_cast<message_66::alarm>(ta | tb);
}

message_66::alarm operator&(message_66::alarm a, message_66::alarm b) noexcept
{
	const uint8_t ta = static_cast<uint8_t>(a);
	const uint8_t tb = static_cast<uint8_t>(b);
	return static_cast<message_66::alarm>(ta & tb);
}
}
}
