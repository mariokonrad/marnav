#include "message_01.hpp"
#include <nmea/unique.hpp> // FIXME: no direct dependency to other libraries, for now

namespace ais
{

std::unique_ptr<message> message_01::parse(const raw& bits) throw(std::invalid_argument)
{
	if (bits.size() != 168)
		throw std::invalid_argument{"invalid number of bits in message_01::parse"};

	std::unique_ptr<message> result = std::make_unique<message_01>();
	message_01& msg = static_cast<message_01&>(*result);

	// TODO: implementation

	bits.get(msg.repeat_indicator, 6, 2);
	bits.get(msg.mmsi, 8, 30);

	return result;
}

}
