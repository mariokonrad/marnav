#include "message_08.hpp"
#include <marnav/ais/binary_001_11.hpp>
#include <marnav/ais/binary_200_10.hpp>

namespace marnav
{
namespace ais
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
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, dac);
	get(bits, fid);

	payload = raw{bits.begin() + SIZE_BITS_HEAD, bits.end()};
}

raw message_08::get_data() const
{
	raw bits(SIZE_BITS_HEAD);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, dac);
	set(bits, fid);

	bits.append(payload);

	return bits;
}

void message_08::read_binary(binary_001_11 & m) const
{
	if (std::make_tuple(1, 11) != std::tie(dac, fid))
		throw std::invalid_argument{"invalid DAC/FID for Meteo/Hydro IMO236"};
	m.read_from(payload);
}

void message_08::write_binary(const binary_001_11 & m)
{
	m.write_to(payload);
}

void message_08::read_binary(binary_200_10 & m) const
{
	if (std::make_tuple(200, 10) != std::tie(dac, fid))
		throw std::invalid_argument{
			"invalid DAC/FID for Inland ship static voyage related data"};
	m.read_from(payload);
}

void message_08::write_binary(const binary_200_10 & m)
{
	m.write_to(payload);
}
}
}
