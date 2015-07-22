#include "message_11.hpp"
#include "angle.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{
message_11::message_11()
	: message_04(ID)
{
}

std::unique_ptr<message> message_11::parse(const raw & bits) throw(std::invalid_argument)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_11::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_11>();
	message_11 & msg = static_cast<message_11 &>(*result);

	msg.read_data(bits);

	return result;
}

}
}
