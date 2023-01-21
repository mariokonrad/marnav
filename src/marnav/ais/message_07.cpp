#include <marnav/ais/message_07.hpp>

namespace marnav::ais
{
constexpr message_id message_07::ID;
constexpr std::size_t message_07::SIZE_BITS_MIN;
constexpr std::size_t message_07::SIZE_BITS_MAX;

message_07::message_07()
	: message(ID)
{
}

message_07::message_07(const raw & bits)
	: message(ID)
{
	if ((bits.size() < SIZE_BITS_MIN) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in ais/message_07"};
	read_data(bits);
}

void message_07::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, mmsi_1_);
	get(bits, mmsi_seq_1_);

	if (bits.size() > SIZE_BITS_MIN + 1 * 32) {
		get(bits, mmsi_2_);
		get(bits, mmsi_seq_2_);
	}
	if (bits.size() > SIZE_BITS_MIN + 2 * 32) {
		get(bits, mmsi_3_);
		get(bits, mmsi_seq_3_);
	}
	if (bits.size() > SIZE_BITS_MIN + 3 * 32) {
		get(bits, mmsi_4_);
		get(bits, mmsi_seq_4_);
	}
}

raw message_07::get_data() const
{
	raw bits(SIZE_BITS_MIN);
	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, mmsi_1_);
	set(bits, mmsi_seq_1_);
	if (mmsi_2_ != 0) {
		set(bits, mmsi_2_);
		set(bits, mmsi_seq_2_);
	}
	if (mmsi_3_ != 0) {
		set(bits, mmsi_3_);
		set(bits, mmsi_seq_3_);
	}
	if (mmsi_4_ != 0) {
		set(bits, mmsi_4_);
		set(bits, mmsi_seq_4_);
	}
	return bits;
}
}
