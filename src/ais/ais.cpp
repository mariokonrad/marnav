#include "ais.hpp"
#include "bitset.hpp"
#include "message_01.hpp"
#include <algorithm>

namespace ais
{

static inline uint8_t decode_armoring(char c)
{
	uint8_t value = c - '0';
	if (value > 40)
		value -= 8;
	return value & 0x3f;
}

static raw collect(const std::vector<std::pair<std::string, int>>& v)
{
	raw result;
	result.reserve(64); // 64 bytes (512) are enough for AIS messages

	for (auto const& item : v) {
		const std::string& payload = item.first;
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

static message::parse_function instantiate_message(message_id type) throw(std::invalid_argument)
{
	using entry = std::pair<message_id, message::parse_function>;
	static const std::vector<entry> known_messages = {
		{message_id::position_report_class_a, message_01::parse},
	};

	auto const& i = std::find_if(begin(known_messages), end(known_messages),
								 [type](const entry& e) { return e.first == type; });

	if (i == end(known_messages))
		throw std::invalid_argument{"unknown message in instantiate_message: "
									+ std::to_string(static_cast<uint8_t>(type))};

	return i->second;
}

std::unique_ptr<message>
make_message(const std::vector<std::pair<std::string, int>>& v) throw(std::invalid_argument)
{
	auto bits = collect(v);
	message_id type = static_cast<message_id>(bits.get<uint8_t>(0, 6));
	return instantiate_message(type)(bits);
}

}

