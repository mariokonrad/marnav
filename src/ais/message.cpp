#include "message.hpp"

namespace ais
{

message::message(message_id type)
	: message_type(type)
{
}

message_id message::type() const { return message_type; }

}
