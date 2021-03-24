#include <marnav/seatalk/message_36.hpp>
#include <stdexcept>

namespace marnav
{
namespace seatalk
{

message_36::message_36()
	: message(ID)
{
}

std::unique_ptr<message> message_36::parse(const raw & data)
{
	check_size(data, SIZE);
	if (data[2] != 0x01)
		throw std::invalid_argument{"invalid data specified in message"};

	return std::make_unique<message_36>();
}

raw message_36::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x00, 0x01};
}
}
}
