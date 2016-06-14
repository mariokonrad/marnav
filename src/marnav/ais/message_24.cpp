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
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);

	std::underlying_type<part>::type tmp = 3;
	bits.get(tmp, 38, 2);
	part_number = static_cast<part>(tmp);

	if (part_number == part::A) {
		shipname = read_string(bits, 40, 20);
		// spare: 160 - 167
	} else {
		bits.get(shiptype, 40, 8);
		vendor_id = read_string(bits, 48, 3);
		bits.get(model, 66, 4);
		bits.get(serial, 70, 20);
		callsign = read_string(bits, 90, 7);
		if (is_auxiliary_vessel()) {
			bits.get(mothership_mmsi, 132, 30);
		} else {
			bits.get(to_bow, 132, 9);
			bits.get(to_stern, 141, 9);
			bits.get(to_port, 150, 6);
			bits.get(to_starboard, 156, 6);
		}
		// spare: 162 - 167
	}
}

raw message_24::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(repeat_indicator, 6, 2);
	bits.set(mmsi, 8, 30);
	bits.set(static_cast<std::underlying_type<part>::type>(part_number), 38, 2);

	if (part_number == part::A) {
		write_string(bits, 40, 20, shipname);
	} else {
		bits.set(shiptype, 40, 8);
		write_string(bits, 48, 3, vendor_id);
		bits.set(model, 66, 4);
		bits.set(serial, 70, 20);
		write_string(bits, 90, 7, callsign);
		if (is_auxiliary_vessel()) {
			bits.set(mothership_mmsi, 132, 30);
		} else {
			bits.set(to_bow, 132, 9);
			bits.set(to_stern, 141, 9);
			bits.set(to_port, 150, 6);
			bits.set(to_starboard, 156, 6);
		}
	}

	return bits;
}
}
}
