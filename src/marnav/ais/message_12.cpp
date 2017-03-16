#include "message_12.hpp"

namespace marnav
{
namespace ais
{
constexpr std::size_t message_12::SIZE_TEXT_MAX;

message_12::message_12()
	: message(ID)
{
}

message_12::message_12(const raw & bits)
	: message(ID)
{
	if ((bits.size() < SIZE_BITS_HEAD) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in ais/message_12"};
	read_data(bits);
}

void message_12::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, seqno);
	get(bits, dest_mmsi);
	get(bits, retransmit);

	auto rest = static_cast<decltype(SIZE_BITS_MAX)>(bits.size()) - SIZE_BITS_HEAD;
	if (rest > 0) {
		rest = std::min(rest, SIZE_BITS_MAX - SIZE_BITS_HEAD);
		text = read_string(bits, 72, rest / 6);
	}
}

raw message_12::get_data() const
{
	raw bits{SIZE_BITS_HEAD};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, seqno);
	set(bits, dest_mmsi);
	set(bits, retransmit);

	if (text.size() > 0) {
		// compute number of bits, must be on a 8-bit boundary
		auto size = text.size() * 6;
		if ((size % 8) != 0)
			size += 8 - (size % 8);

		if (size <= SIZE_BITS_MAX - SIZE_BITS_HEAD) {
			// append a temporary bitset to the real one
			raw t{size};
			write_string(t, 0, text.size(), text);
			bits.append(t);
		}
	}

	return bits;
}

void message_12::set_seqno(uint32_t t)
{
	if (t > 3u)
		throw std::invalid_argument{"set_seqno out of range [0..3]"};
	seqno = t;
}

void message_12::set_text(const std::string & t)
{
	text = t.substr(0, std::min(t.size(), SIZE_TEXT_MAX));
}
}
}
