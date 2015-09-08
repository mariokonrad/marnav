#include "message_10.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_10::message_10()
	: message(ID)
	, repeat_indicator(0)
	, mmsi(0)
	, dest_mmsi(0)
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
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	// spare 38 - 39
	bits.get(dest_mmsi, 40, 30);
	// spare 70 - 71
}

raw message_10::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(mmsi, 8, 30);
	bits.set(dest_mmsi, 40, 30);

	return bits;
}
}
}
