#include "message_21.hpp"

#include <algorithm>

#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_21::message_21()
	: message(ID)
	, repeat_indicator(0)
	, mmsi(0)
	, aid_type(aid_type_id::unspecified)
	, name("@@@@@@@@@@@@@@@@@@@@")
	, position_accuracy(false)
	, longitude_minutes(0)
	, latitude_minutes(0)
	, to_bow(0)
	, to_stern(0)
	, to_port(0)
	, to_starboard(0)
	, epfd_fix()
	, utc_second(0)
	, off_position(off_position_indicator::off_position)
	, regional(0)
	, raim(false)
	, virtual_aid_flag(virtual_aid::virtual_aid)
	, assigned(false)
{
}

std::unique_ptr<message> message_21::parse(const raw & bits)
{
	if ((bits.size() < SIZE_BITS_MIN) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in message_21::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_21>();
	message_21 & msg = static_cast<message_21 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_21::read_data(const raw & bits)
{
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	bits.get(aid_type, 38, 5);
	name = read_string(bits, 43, 20);
	bits.get(position_accuracy, 163, 1);
	bits.get(longitude_minutes, 164, 28);
	bits.get(latitude_minutes, 192, 27);
	bits.get(to_bow, 219, 9);
	bits.get(to_stern, 228, 9);
	bits.get(to_port, 237, 6);
	bits.get(to_starboard, 243, 6);
	bits.get(epfd_fix, 249, 4);
	bits.get(utc_second, 253, 6);
	bits.get(regional, 259, 1);
	bits.get(regional, 260, 8);
	bits.get(raim, 268, 1);
	bits.get(virtual_aid_flag, 269, 1);
	bits.get(assigned, 270, 1);
	// spare: 271 - 271

	auto rest = static_cast<decltype(SIZE_BITS_MAX)>(bits.size()) - SIZE_BITS_MIN;
	if (rest > 0) {
		rest = std::min(rest, SIZE_BITS_MAX - SIZE_BITS_MIN);
		name_extension = read_string(bits, 272, rest  / 6);
	}
}

/// @todo possible refactoring for name_extension
raw message_21::get_data() const
{
	raw bits{SIZE_BITS_MIN};

	bits.set(type(), 0, 6);
	bits.set(mmsi, 8, 30);
	bits.set(aid_type, 38, 5);
	write_string(bits, 43, 20, name);
	bits.set(position_accuracy, 163, 1);
	bits.set(longitude_minutes, 164, 28);
	bits.set(latitude_minutes, 192, 27);
	bits.set(to_bow, 219, 9);
	bits.set(to_stern, 228, 9);
	bits.set(to_port, 237, 6);
	bits.set(to_starboard, 243, 6);
	bits.set(epfd_fix, 249, 4);
	bits.set(utc_second, 253, 6);
	bits.set(regional, 259, 1);
	bits.set(regional, 260, 8);
	bits.set(raim, 268, 1);
	bits.set(virtual_aid_flag, 269, 1);
	bits.set(assigned, 270, 1);

	if (name_extension.size() > 0) {
		// compute number of bits, must be on a 8-bit boundary
		auto size = name_extension.size() * 6;
		if ((size % 8) != 0)
			size += 8 - (size % 8);

		if (size <= SIZE_BITS_MAX - SIZE_BITS_MIN) {
			// append a temporary bitset to the real one
			raw t{size};
			write_string(t, 0, name_extension.size(), name_extension);
			bits.append(t);
		}
	}

	return bits;
}

void message_21::set_name(const std::string & t)
{
	if (t.size() > 20) {
		name = t.substr(0, 20);
	} else {
		name = t;
	}
}

void message_21::set_name_extension(const std::string & t)
{
	// 88 bits with 6-bit encoding are 14 characters
	if (t.size() > 14) {
		name_extension = t.substr(0, 14);
	} else {
		name_extension = t;
	}
}

geo::longitude message_21::get_longitude() const { return to_geo_longitude(longitude_minutes); }

geo::latitude message_21::get_latitude() const { return to_geo_latitude(latitude_minutes); }

void message_21::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_21::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}
}
}
