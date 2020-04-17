#include <marnav/seatalk/message.hpp>
#include <stdexcept>
#include <cassert>

namespace marnav
{
namespace seatalk
{

message::message(message_id id)
	: message_type_(id)
{
}

message_id message::type() const
{
	return message_type_;
}

/// Checks the specified sizes for the raw data. In case of error, an
/// exception is thrown (std::invalid_argument).
///
/// This check must be done for every message.
void message::check_size(const raw & data, size_t size)
{
	assert(size > 2);

	if (data.size() != size)
		throw std::invalid_argument{"invalid number of bytes in message"};
	if ((data[1] & 0x0f) != static_cast<uint8_t>(size - 3))
		throw std::invalid_argument{"invalid size specified in message"};
}
}
}
