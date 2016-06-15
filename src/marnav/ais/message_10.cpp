#include "message_10.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{
message_10::message_10()
	: message(ID)
{
}

std::unique_ptr<message> message_10::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_10::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_10>();
	message_10 & msg = static_cast<message_10 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_10::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, dest_mmsi);
}

raw message_10::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, dest_mmsi);

	return bits;
}
}
}
