#include <marnav/seatalk/message_66.hpp>

namespace marnav::seatalk
{

message_66::message_66()
	: message(ID)
{
}

std::unique_ptr<message> message_66::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = std::make_unique<message_66>();
	auto & msg = static_cast<message_66 &>(*result);

	//  66 00 XX
	// raw  1  2

	msg.value_ = static_cast<alarm>(data[2]);

	return result;
}

raw message_66::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x00, value_};
}

message_66::alarm operator|(message_66::alarm a, message_66::alarm b) noexcept
{
	const auto ta = static_cast<uint8_t>(a);
	const auto tb = static_cast<uint8_t>(b);
	return static_cast<message_66::alarm>(ta | tb);
}

message_66::alarm operator&(message_66::alarm a, message_66::alarm b) noexcept
{
	const auto ta = static_cast<uint8_t>(a);
	const auto tb = static_cast<uint8_t>(b);
	return static_cast<message_66::alarm>(ta & tb);
}
}
