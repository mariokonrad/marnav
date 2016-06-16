#include "message_11.hpp"
#include <marnav/ais/angle.hpp>

namespace marnav
{
namespace ais
{
MARNAV_AIS_DEFINE_MESSAGE_PARSE_FUNC(message_11)

message_11::message_11()
	: message_04(ID)
{
}

message_11::message_11(const raw & bits)
	: message_04(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_11"};
	read_data(bits);
}
}
}
