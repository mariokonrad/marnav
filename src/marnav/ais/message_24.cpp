#include "message_24.hpp"
#include <type_traits>
#include <marnav/utils/unique.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

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

std::unique_ptr<message> message_24::parse(const raw & bits)
{
	if ((bits.size() != SIZE_BITS) && (bits.size() != SIZE_BITS_IGNORED_SPARES_OF_TYPE_A))
		throw std::invalid_argument{"invalid number of bits in message_24::parse"};

	uint32_t part = 3;
	bits.get(part, 38, 2);

	if (part > 1)
		throw std::invalid_argument{"invalid part number message_24::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_24>();
	message_24 & msg = static_cast<message_24 &>(*result);

	msg.read_data(bits);

	return result;
}

bool message_24::is_auxiliary_vessel() const { return utils::mmsi{mmsi}.is_auxiliary(); }

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
	raw bits{SIZE_BITS};

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
}
}
