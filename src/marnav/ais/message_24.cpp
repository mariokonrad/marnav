#include "message_24.hpp"
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{
constexpr message_id message_24::ID;
constexpr std::size_t message_24::SIZE_BITS;
constexpr std::size_t message_24::SIZE_BITS_IGNORED_SPARES_OF_TYPE_A;

message_24::message_24()
	: message_24(ID)
{
}

message_24::message_24(message_id id)
	: message(id)
	, shipname("@@@@@@@@@@@@@@@@@@@@")
	, vendor_id("@@@")
	, callsign("@@@@@@@")
{
}

message_24::message_24(const raw & bits)
	: message_24(ID)
{
	if ((bits.size() != SIZE_BITS) && (bits.size() != SIZE_BITS_IGNORED_SPARES_OF_TYPE_A))
		throw std::invalid_argument{"invalid number of bits in ais/message_24"};

	get(bits, part_number);
	if ((part_number != part::A) && (part_number != part::B))
		throw std::invalid_argument{"invalid part number ais/message_24"};
	read_data(bits);
}

bool message_24::is_auxiliary_vessel() const
{
	return utils::mmsi{mmsi}.is_auxiliary();
}

void message_24::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, part_number);

	if (part_number == part::A) {
		get(bits, shipname);
	} else {
		get(bits, shiptype);
		get(bits, vendor_id);
		get(bits, model);
		get(bits, serial);
		get(bits, callsign);
		if (is_auxiliary_vessel()) {
			get(bits, mothership_mmsi);
		} else {
			get(bits, to_bow);
			get(bits, to_stern);
			get(bits, to_port);
			get(bits, to_starboard);
		}
	}
}

raw message_24::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, part_number);

	if (part_number == part::A) {
		set(bits, shipname);
	} else {
		set(bits, shiptype);
		set(bits, vendor_id);
		set(bits, model);
		set(bits, serial);
		set(bits, callsign);
		if (is_auxiliary_vessel()) {
			set(bits, mothership_mmsi);
		} else {
			set(bits, to_bow);
			set(bits, to_stern);
			set(bits, to_port);
			set(bits, to_starboard);
		}
	}

	return bits;
}

std::string message_24::get_shipname() const
{
	return trim_ais_string(shipname);
}

std::string message_24::get_vendor_id() const
{
	return trim_ais_string(vendor_id);
}

std::string message_24::get_callsign() const
{
	return trim_ais_string(callsign);
}

void message_24::set_shipname(const std::string & t)
{
	if (t.size() > 20) {
		shipname = t.substr(0, 20);
	} else {
		shipname = t;
	}
}

void message_24::set_vendor_id(const std::string & t)
{
	if (t.size() > 3) {
		callsign = t.substr(0, 3);
	} else {
		callsign = t;
	}
}

void message_24::set_callsign(const std::string & t)
{
	if (t.size() > 7) {
		callsign = t.substr(0, 7);
	} else {
		callsign = t;
	}
}
}
}
