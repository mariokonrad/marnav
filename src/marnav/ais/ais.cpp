#include "ais.hpp"

#include <algorithm>

#include <marnav/ais/message_01.hpp>
#include <marnav/ais/message_02.hpp>
#include <marnav/ais/message_03.hpp>
#include <marnav/ais/message_04.hpp>
#include <marnav/ais/message_05.hpp>
#include <marnav/ais/message_06.hpp>
#include <marnav/ais/message_08.hpp>
#include <marnav/ais/message_09.hpp>
#include <marnav/ais/message_10.hpp>
#include <marnav/ais/message_11.hpp>
#include <marnav/ais/message_18.hpp>
#include <marnav/ais/message_19.hpp>
#include <marnav/ais/message_21.hpp>
#include <marnav/ais/message_22.hpp>
#include <marnav/ais/message_23.hpp>
#include <marnav/ais/message_24.hpp>

/// @example parse_ais.cpp
/// This example shows how to parse AIS messages from NMEA sentences.

/// @example read_ais.cpp
/// This is an example on how to parse and handle AIS messages while
/// receiving NMEA sentences.

/// @example create_nmea_from_ais.cpp
/// Shows how to create a NMEA sentence or sentences from AIS data.

namespace marnav
{
namespace ais
{
uint8_t decode_armoring(char c)
{
	auto value = c - '0';
	if (value > 40)
		value -= 8;
	return value & 0x3f;
}

char encode_armoring(uint8_t value)
{
	value &= 0x3f; // ensure 6 bits
	if (value > 39)
		value += 8;
	return value + '0';
}

/// @cond DEV

namespace
{
static raw collect(const std::vector<std::pair<std::string, uint32_t>> & v)
{
	raw result;
	result.reserve(64); // 64 bytes (512) are enough for AIS messages

	for (auto const & item : v) {
		const std::string & payload = item.first;
		const uint32_t pad = item.second;

		auto end = payload.cend();
		auto last = end - 1;
		for (auto i = payload.cbegin(); i != end; ++i) {

			uint8_t value = decode_armoring(*i);

			if (i == last) {
				result.append(value >> pad, 6 - pad);
			} else {
				result.append(value, 6);
			}
		}
	}

	return result;
}

static std::function<std::unique_ptr<message>(const raw &)> instantiate_message(
	message_id type, size_t size)
{
#define REGISTER_MESSAGE(m)      \
	{                            \
		m::ID, detail::parse_##m \
	}

	struct entry {
		const message_id id;
		const std::function<std::unique_ptr<message>(const raw &)> parse;
	};

	static const std::vector<entry> known_messages = {
		REGISTER_MESSAGE(message_01), REGISTER_MESSAGE(message_02),
		REGISTER_MESSAGE(message_03), REGISTER_MESSAGE(message_04),
		REGISTER_MESSAGE(message_05), REGISTER_MESSAGE(message_06),
		REGISTER_MESSAGE(message_08), REGISTER_MESSAGE(message_09),
		REGISTER_MESSAGE(message_10), REGISTER_MESSAGE(message_11),
		REGISTER_MESSAGE(message_18), REGISTER_MESSAGE(message_19),
		REGISTER_MESSAGE(message_21), REGISTER_MESSAGE(message_22),
		REGISTER_MESSAGE(message_23), REGISTER_MESSAGE(message_24),
	};

#undef REGISTER_MESSAGE

	using namespace std;
	auto const & i = std::find_if(begin(known_messages), end(known_messages),
		[type](const entry & e) { return e.id == type; });

	if (i == end(known_messages))
		throw unknown_message{"unknown message in ais/instantiate_message: "
			+ std::to_string(static_cast<uint8_t>(type)) + " (" + std::to_string(size)
			+ " bits)"};

	return i->parse;
}
}

/// @endcond

/// Parses the specified data and creates corresponding AIS messages.
///
/// @param[in] v All NMEA payloads, necessary to build the AIS message.
///  This may be obtained using nmea::collect_payload.
/// @return The constructed AIS message.
/// @exception unknown_message Will be thrown if the AIS message is not supported.
/// @exception std::invalid_argument Error has been occurred during parsing of
///   the message.
std::unique_ptr<message> make_message(const std::vector<std::pair<std::string, uint32_t>> & v)
{
	auto bits = collect(v);
	message_id type = static_cast<message_id>(bits.get<uint8_t>(0, 6));
	return instantiate_message(type, bits.size())(bits);
}

/// Encodes the specified message and returns a container with payload and padding
/// information. This payload container can be used directly with NMEA funcitons.
///
/// @param[in] msg The message to encode.
/// @return The container with payload/padding information
///
std::vector<std::pair<std::string, uint32_t>> encode_message(const message & msg)
{
	auto bits = msg.get_data();
	if (bits.size() == 0)
		throw std::invalid_argument{"message not able to encode"};

	std::vector<std::pair<std::string, uint32_t>> result;

	std::pair<std::string, uint32_t> current{"", 0};
	for (raw::size_type ofs = 0; ofs < bits.size(); ofs += 6) {
		if (ofs + 6 < bits.size()) {
			// normal case

			uint8_t value = 0;
			bits.get(value, ofs, 6);
			current.first += encode_armoring(value);

			// append to string, only 51 characters per string (happens to be NMEA restriction)
			if (current.first.size() == 56) {
				result.push_back(current);
				current.first.clear();
				current.second = 0;
			}
		} else {
			// last, append remainder padded to the string

			auto remainder = bits.size() - ofs;
			current.second = 6 - remainder;
			uint8_t value = 0;
			bits.get(value, ofs, remainder);
			value <<= current.second;
			current.first += encode_armoring(value);
			result.push_back(current);
		}
	}

	return result;
}
}
}
