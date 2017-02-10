#include "message_06.hpp"

namespace marnav
{
namespace ais
{
message_06::message_06()
	: message(ID)
{
}

message_06::message_06(const raw & bits)
	: message(ID)
{
	if ((bits.size() < SIZE_BITS_HEAD) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in ais/message_06"};
	read_data(bits);
}

void message_06::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, sequence_no);
	get(bits, dest_mmsi);
	get(bits, retransmit_flag);
	get(bits, dac);
	get(bits, fid);

	payload = raw{bits.begin() + SIZE_BITS_HEAD, bits.end()};
}

raw message_06::get_data() const
{
	raw bits{SIZE_BITS_HEAD};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, sequence_no);
	set(bits, dest_mmsi);
	set(bits, retransmit_flag);
	set(bits, dac);
	set(bits, fid);

	bits.append(payload);

	return bits;
}
}
}
