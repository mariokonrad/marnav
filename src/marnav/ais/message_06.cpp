#include <marnav/ais/message_06.hpp>

namespace marnav::ais
{
constexpr message_id message_06::ID;
constexpr std::size_t message_06::SIZE_BITS_HEAD;
constexpr std::size_t message_06::SIZE_BITS_MAX;

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
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, sequence_no_);
	get(bits, dest_mmsi_);
	get(bits, retransmit_flag_);
	get(bits, dac_);
	get(bits, fid_);

	payload_ = raw{bits.begin() + SIZE_BITS_HEAD, bits.end()};
}

raw message_06::get_data() const
{
	raw bits(SIZE_BITS_HEAD);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, sequence_no_);
	set(bits, dest_mmsi_);
	set(bits, retransmit_flag_);
	set(bits, dac_);
	set(bits, fid_);

	bits.append(payload_);

	return bits;
}
}
