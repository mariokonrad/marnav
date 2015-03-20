#include "message.hpp"

namespace seatalk
{
message::message(message_id id)
	: message_type(id)
{
}

message_id message::type() const
{
	return message_type;
}
}
