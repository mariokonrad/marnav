#include "message_01.hpp"
#include <utils/unique.hpp>

namespace ais
{

message_01::message_01()
	: message(ID)
{
}

std::unique_ptr<message> message_01::parse(const raw& bits) throw(std::invalid_argument)
{
	if (bits.size() != 168)
		throw std::invalid_argument{"invalid number of bits in message_01::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_01>();
	message_01& msg = static_cast<message_01&>(*result);

	msg.read_data(bits);

	return result;
}

void message_01::read_data(const raw& bits)
{
	// TODO: implementation

	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
}

}
