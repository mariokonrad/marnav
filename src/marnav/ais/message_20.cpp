#include "message_20.hpp"
#include <stdexcept>

namespace marnav
{
namespace ais
{
constexpr message_id message_20::ID;
constexpr std::size_t message_20::SIZE_BITS_MIN;
constexpr std::size_t message_20::SIZE_BITS_MAX;

message_20::message_20()
	: message(ID)
{
}

message_20::message_20(const raw & bits)
	: message(ID)
{
	if ((bits.size() < SIZE_BITS_MIN) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in ais/message_20"};
	read_data(bits);
}

void message_20::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, offset_number_1);
	get(bits, reserved_slots_1);
	get(bits, timeout_1);
	get(bits, increment_1);

	if (bits.size() > SIZE_BITS_MIN + 1 * 30) {
		get(bits, offset_number_2);
		get(bits, reserved_slots_2);
		get(bits, timeout_2);
		get(bits, increment_2);
	}
	if (bits.size() > SIZE_BITS_MIN + 2 * 30) {
		get(bits, offset_number_3);
		get(bits, reserved_slots_3);
		get(bits, timeout_3);
		get(bits, increment_3);
	}
	if (bits.size() > SIZE_BITS_MIN + 3 * 30) {
		get(bits, offset_number_4);
		get(bits, reserved_slots_4);
		get(bits, timeout_4);
		get(bits, increment_4);
	}
}

raw message_20::get_data() const
{
	raw bits(SIZE_BITS_MIN);
	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, offset_number_1);
	set(bits, reserved_slots_1);
	set(bits, timeout_1);
	set(bits, increment_1);
	if (offset_number_2 != 0) {
		set(bits, offset_number_2);
		set(bits, reserved_slots_2);
		set(bits, timeout_2);
		set(bits, increment_2);
	}
	if (offset_number_3 != 0) {
		set(bits, offset_number_3);
		set(bits, reserved_slots_3);
		set(bits, timeout_3);
		set(bits, increment_3);
	}
	if (offset_number_4 != 0) {
		set(bits, offset_number_4);
		set(bits, reserved_slots_4);
		set(bits, timeout_4);
		set(bits, increment_4);
	}
	return bits;
}

message_20::entry message_20::get_entry(int index) const
{
	if (index < 0 || index > 3)
		throw std::out_of_range{"index out of range"};
	switch (index) {
		case 0:
			return {offset_number_1, reserved_slots_1, timeout_1, increment_1};
		case 1:
			return {offset_number_2, reserved_slots_2, timeout_2, increment_2};
		case 2:
			return {offset_number_3, reserved_slots_3, timeout_3, increment_3};
		case 3:
			return {offset_number_4, reserved_slots_4, timeout_4, increment_4};
	}
	return {};
}

void message_20::set_entry(int index, message_20::entry e)
{
	if (index < 0 || index > 3)
		throw std::out_of_range{"index out of range"};
	switch (index) {
		case 0:
			offset_number_1 = e.offset;
			reserved_slots_1 = e.slots;
			timeout_1 = e.timeout;
			increment_1 = e.increment;
			break;
		case 1:
			offset_number_2 = e.offset;
			reserved_slots_2 = e.slots;
			timeout_2 = e.timeout;
			increment_2 = e.increment;
			break;
		case 2:
			offset_number_3 = e.offset;
			reserved_slots_3 = e.slots;
			timeout_3 = e.timeout;
			increment_3 = e.increment;
			break;
		case 3:
			offset_number_4 = e.offset;
			reserved_slots_4 = e.slots;
			timeout_4 = e.timeout;
			increment_4 = e.increment;
			break;
	}
}
}
}
