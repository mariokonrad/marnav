#include "message_24.hpp"

namespace marnav
{
namespace seatalk
{

message_24::message_24()
	: message(ID)
	, unit(nautical_miles)
{
}

std::unique_ptr<message> message_24::parse(const raw & data) throw(std::invalid_argument)
{
	if (data.size() != 5)
		throw std::invalid_argument{"invalid number of bytes in message_24::parse"};
	if (data[1] != 0x02)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_24>();
	message_24 & msg = static_cast<message_24 &>(*result);

	msg.unit = static_cast<unit_type>(data[4]);

	return result;
}

raw message_24::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x02, 0x00, 0x00, unit};
}
}
}
