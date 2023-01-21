#include <marnav/ais/message_20.hpp>
#include <stdexcept>

namespace marnav::ais
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
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, offset_number_1_);
	get(bits, reserved_slots_1_);
	get(bits, timeout_1_);
	get(bits, increment_1_);

	if (bits.size() > SIZE_BITS_MIN + 1 * 30) {
		get(bits, offset_number_2_);
		get(bits, reserved_slots_2_);
		get(bits, timeout_2_);
		get(bits, increment_2_);
	}
	if (bits.size() > SIZE_BITS_MIN + 2 * 30) {
		get(bits, offset_number_3_);
		get(bits, reserved_slots_3_);
		get(bits, timeout_3_);
		get(bits, increment_3_);
	}
	if (bits.size() > SIZE_BITS_MIN + 3 * 30) {
		get(bits, offset_number_4_);
		get(bits, reserved_slots_4_);
		get(bits, timeout_4_);
		get(bits, increment_4_);
	}
}

raw message_20::get_data() const
{
	raw bits(SIZE_BITS_MIN);
	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, offset_number_1_);
	set(bits, reserved_slots_1_);
	set(bits, timeout_1_);
	set(bits, increment_1_);
	if (offset_number_2_ != 0) {
		set(bits, offset_number_2_);
		set(bits, reserved_slots_2_);
		set(bits, timeout_2_);
		set(bits, increment_2_);
	}
	if (offset_number_3_ != 0) {
		set(bits, offset_number_3_);
		set(bits, reserved_slots_3_);
		set(bits, timeout_3_);
		set(bits, increment_3_);
	}
	if (offset_number_4_ != 0) {
		set(bits, offset_number_4_);
		set(bits, reserved_slots_4_);
		set(bits, timeout_4_);
		set(bits, increment_4_);
	}
	return bits;
}

message_20::entry message_20::get_entry(int index) const
{
	if (index < 0 || index > 3)
		throw std::out_of_range{"index out of range"};
	switch (index) {
		case 0:
			return {offset_number_1_, reserved_slots_1_, timeout_1_, increment_1_};
		case 1:
			return {offset_number_2_, reserved_slots_2_, timeout_2_, increment_2_};
		case 2:
			return {offset_number_3_, reserved_slots_3_, timeout_3_, increment_3_};
		case 3:
			return {offset_number_4_, reserved_slots_4_, timeout_4_, increment_4_};
	}
	return {};
}

void message_20::set_entry(int index, message_20::entry e)
{
	if (index < 0 || index > 3)
		throw std::out_of_range{"index out of range"};
	switch (index) {
		case 0:
			offset_number_1_ = e.offset;
			reserved_slots_1_ = e.slots;
			timeout_1_ = e.timeout;
			increment_1_ = e.increment;
			break;
		case 1:
			offset_number_2_ = e.offset;
			reserved_slots_2_ = e.slots;
			timeout_2_ = e.timeout;
			increment_2_ = e.increment;
			break;
		case 2:
			offset_number_3_ = e.offset;
			reserved_slots_3_ = e.slots;
			timeout_3_ = e.timeout;
			increment_3_ = e.increment;
			break;
		case 3:
			offset_number_4_ = e.offset;
			reserved_slots_4_ = e.slots;
			timeout_4_ = e.timeout;
			increment_4_ = e.increment;
			break;
	}
}
}
