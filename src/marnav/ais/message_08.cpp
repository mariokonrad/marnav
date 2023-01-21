#include <marnav/ais/message_08.hpp>
#include <marnav/ais/binary_001_11.hpp>
#include <marnav/ais/binary_200_10.hpp>

namespace marnav::ais
{
constexpr message_id message_08::ID;
constexpr std::size_t message_08::SIZE_BITS_HEAD;
constexpr std::size_t message_08::SIZE_BITS_MAX;

message_08::message_08()
	: message(ID)
{
}

message_08::message_08(const raw & bits)
	: message(ID)
{
	if ((bits.size() < SIZE_BITS_HEAD) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in ais/message_08"};
	read_data(bits);
}

void message_08::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, dac_);
	get(bits, fid_);

	payload_ = raw{bits.begin() + SIZE_BITS_HEAD, bits.end()};
}

raw message_08::get_data() const
{
	raw bits(SIZE_BITS_HEAD);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, dac_);
	set(bits, fid_);

	bits.append(payload_);

	return bits;
}

void message_08::read_binary(binary_001_11 & m) const
{
	if (std::make_tuple(1, 11) != std::tie(dac_, fid_))
		throw std::invalid_argument{"invalid DAC/FID for Meteo/Hydro IMO236"};
	m.read_from(payload_);
}

void message_08::write_binary(const binary_001_11 & m)
{
	m.write_to(payload_);
}

void message_08::read_binary(binary_200_10 & m) const
{
	if (std::make_tuple(200, 10) != std::tie(dac_, fid_))
		throw std::invalid_argument{
			"invalid DAC/FID for Inland ship static voyage related data"};
	m.read_from(payload_);
}

void message_08::write_binary(const binary_200_10 & m)
{
	m.write_to(payload_);
}
}
