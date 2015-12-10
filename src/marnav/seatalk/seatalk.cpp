#include "seatalk.hpp"

#include <algorithm>

#include <marnav/seatalk/message_00.hpp>
#include <marnav/seatalk/message_01.hpp>
#include <marnav/seatalk/message_05.hpp>
#include <marnav/seatalk/message_10.hpp>
#include <marnav/seatalk/message_11.hpp>
#include <marnav/seatalk/message_20.hpp>
#include <marnav/seatalk/message_21.hpp>
#include <marnav/seatalk/message_22.hpp>
#include <marnav/seatalk/message_23.hpp>
#include <marnav/seatalk/message_24.hpp>
#include <marnav/seatalk/message_25.hpp>
#include <marnav/seatalk/message_26.hpp>
#include <marnav/seatalk/message_27.hpp>
#include <marnav/seatalk/message_30.hpp>
#include <marnav/seatalk/message_36.hpp>
#include <marnav/seatalk/message_38.hpp>
#include <marnav/seatalk/message_50.hpp>
#include <marnav/seatalk/message_51.hpp>
#include <marnav/seatalk/message_52.hpp>
#include <marnav/seatalk/message_53.hpp>
#include <marnav/seatalk/message_54.hpp>
#include <marnav/seatalk/message_56.hpp>
#include <marnav/seatalk/message_58.hpp>
#include <marnav/seatalk/message_59.hpp>
#include <marnav/seatalk/message_66.hpp>
#include <marnav/seatalk/message_6c.hpp>
#include <marnav/seatalk/message_86.hpp>
#include <marnav/seatalk/message_87.hpp>
#include <marnav/seatalk/message_89.hpp>

namespace marnav
{
namespace seatalk
{

namespace
{
// local macro, used for convenience while registering messges
#define REGISTER_MESSAGE(m)      \
	{                            \
		m::ID, m::SIZE, m::parse \
	}

struct entry {
	const message_id id;
	const size_t size;
	const message::parse_function parse;
};

static const std::vector<entry> known_messages = {
	REGISTER_MESSAGE(message_00), REGISTER_MESSAGE(message_01), REGISTER_MESSAGE(message_05),
	REGISTER_MESSAGE(message_10), REGISTER_MESSAGE(message_11), REGISTER_MESSAGE(message_20),
	REGISTER_MESSAGE(message_21), REGISTER_MESSAGE(message_22), REGISTER_MESSAGE(message_23),
	REGISTER_MESSAGE(message_23), REGISTER_MESSAGE(message_25), REGISTER_MESSAGE(message_26),
	REGISTER_MESSAGE(message_27), REGISTER_MESSAGE(message_30), REGISTER_MESSAGE(message_36),
	REGISTER_MESSAGE(message_38), REGISTER_MESSAGE(message_50), REGISTER_MESSAGE(message_51),
	REGISTER_MESSAGE(message_52), REGISTER_MESSAGE(message_53), REGISTER_MESSAGE(message_54),
	REGISTER_MESSAGE(message_56), REGISTER_MESSAGE(message_58), REGISTER_MESSAGE(message_59),
	REGISTER_MESSAGE(message_66), REGISTER_MESSAGE(message_6c), REGISTER_MESSAGE(message_86),
	REGISTER_MESSAGE(message_87), REGISTER_MESSAGE(message_89),
};

#undef REGISTER_MESSAGE
}

/// @cond DEV
namespace detail
{
static message::parse_function instantiate_message(message_id type)
{
	auto const & i = std::find_if(begin(known_messages), end(known_messages),
		[type](const entry & e) { return e.id == type; });

	if (i == end(known_messages))
		throw std::invalid_argument{"unknown message in instantiate_message: "
			+ std::to_string(static_cast<uint8_t>(type))};

	return i->parse;
}
}
/// @endcond

/// Creates and returns a SeaTalk message from the specified raw data.
///
/// @param[in] data Raw data to parse and interpret.
/// @return The created message.
/// @exception std::invalid_argument Specified raw data is invalid or
///   data cannot be processed.
std::unique_ptr<message> make_message(const raw & data)
{
	if (data.size() < 1)
		throw std::invalid_argument{"raw data of insufficient size"};
	message_id type = static_cast<message_id>(data[0]);
	return detail::instantiate_message(type)(data);
}

/// Returns the raw data from a specific SeaTalk message.
///
/// @param[in] msg The message to convert to raw data.
/// @return The raw data, generated from the specified message.
///
/// @b Example: getting raw data from message
/// @snippet seatalk_snippets.cpp Getting raw data from message
///
raw encode_message(const message & msg) { return msg.get_data(); }

/// Returns the message size of the specified message id.
///
/// @param[in] id ID of the message to get the size for.
/// @return The size of the specified message.
/// @exception std::invalid_argument Thrown if the specified message ID is invalid.
size_t message_size(message_id id)
{
	auto const & i = std::find_if(begin(known_messages), end(known_messages),
		[id](const entry & e) { return e.id == id; });

	if (i == end(known_messages))
		throw std::invalid_argument{
			"unknown message in message_size: " + std::to_string(static_cast<uint8_t>(id))};

	return i->size;
}
}
}
