#include <marnav/seatalk/message_65.hpp>

namespace marnav
{
namespace seatalk
{
message_65::message_65()
	: message(ID)
{
}

std::unique_ptr<message> message_65::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_65>();

	return result;
}

raw message_65::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x00, 0x02};
}
}
}
