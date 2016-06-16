#include "message_02.hpp"

namespace marnav
{
namespace ais
{
MARNAV_AIS_DEFINE_MESSAGE_PARSE_FUNC(message_02)

message_02::message_02()
	: message_01(ID)
{
}

message_02::message_02(const raw & bits)
	: message_01(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in ais/message_02"};
	read_data(bits);
}
}
}
