#include <marnav/ais/message_14.hpp>

namespace marnav::ais
{
constexpr message_id message_14::ID;
constexpr std::size_t message_14::SIZE_BITS_HEAD;
constexpr std::size_t message_14::SIZE_BITS_MAX;
constexpr std::size_t message_14::SIZE_TEXT_MAX;

message_14::message_14()
	: message(ID)
{
}

message_14::message_14(const raw & bits)
	: message(ID)
{
	if ((bits.size() < SIZE_BITS_HEAD) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in ais/message_14"};
	read_data(bits);
}

void message_14::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);

	auto rest = bits.size() - SIZE_BITS_HEAD;
	if (rest > 0) {
		rest = std::min(rest, SIZE_BITS_MAX - SIZE_BITS_HEAD);
		text_ = read_string(bits, 40, rest / 6);
	}
}

raw message_14::get_data() const
{
	raw bits(SIZE_BITS_HEAD);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);

	if (text_.size() > 0) {
		// compute number of bits, must be on a 8-bit boundary
		auto size = text_.size() * 6;
		if ((size % 8) != 0)
			size += 8 - (size % 8);

		if (size <= SIZE_BITS_MAX - SIZE_BITS_HEAD) {
			// append a temporary bitset to the real one
			raw t(size);
			write_string(t, 0, text_.size(), text_);
			bits.append(t);
		}
	}

	return bits;
}

void message_14::set_text(const std::string & t)
{
	text_ = t.substr(0, std::min(t.size(), SIZE_TEXT_MAX));
}
}
