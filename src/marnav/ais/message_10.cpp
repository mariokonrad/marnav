#include "message_10.hpp"
#include <marnav/ais/angle.hpp>

namespace marnav
{
namespace ais
{
constexpr message_id message_10::ID;
constexpr std::size_t message_10::SIZE_BITS;

message_10::message_10()
	: message(ID)
{
}

message_10::message_10(const raw & bits)
	: message(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_10"};
	read_data(bits);
}

void message_10::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, dest_mmsi);
}

raw message_10::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, dest_mmsi);

	return bits;
}
}
}
