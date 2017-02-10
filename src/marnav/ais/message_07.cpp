#include "message_07.hpp"

namespace marnav
{
namespace ais
{
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
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, mmsi_1);
	get(bits, mmsi_seq_1);

	if (bits.size() > SIZE_BITS_MIN + 1 * 32) {
		get(bits, mmsi_2);
		get(bits, mmsi_seq_2);
	}
	if (bits.size() > SIZE_BITS_MIN + 2 * 32) {
		get(bits, mmsi_3);
		get(bits, mmsi_seq_3);
	}
	if (bits.size() > SIZE_BITS_MIN + 3 * 32) {
		get(bits, mmsi_4);
		get(bits, mmsi_seq_4);
	}
}

raw message_07::get_data() const
{
	raw bits{SIZE_BITS_MIN};
	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, mmsi_1);
	set(bits, mmsi_seq_1);
	if (mmsi_2 != 0) {
		set(bits, mmsi_2);
		set(bits, mmsi_seq_2);
	}
	if (mmsi_3 != 0) {
		set(bits, mmsi_3);
		set(bits, mmsi_seq_3);
	}
	if (mmsi_4 != 0) {
		set(bits, mmsi_4);
		set(bits, mmsi_seq_4);
	}
	return bits;
}
}
}
