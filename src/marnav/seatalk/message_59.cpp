#include "message_59.hpp"

namespace marnav
{
namespace seatalk
{
namespace
{
static uint8_t ensure_range(uint8_t value, uint8_t min, uint8_t max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}
}

message_59::message_59()
	: message(ID)
	, hours_(0)
	, minutes_(0)
	, seconds_(0)
	, count_mode_(mode::up_and_start)
{
}

std::unique_ptr<message> message_59::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_59>();
	message_59 & msg = static_cast<message_59 &>(*result);

	//  59 22 SS MM XH
	// raw  1  2  3  4

	msg.hours_ = ensure_range(data[4] & 0x0f, 0, 9);
	msg.seconds_ = ensure_range(data[2], 0, 59);
	msg.minutes_ = ensure_range(data[3], 0, 59);
	msg.count_mode_ = static_cast<mode>((data[4] >> 4) & 0x0f);

	return result;
}

raw message_59::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x22, seconds_, minutes_,
		static_cast<uint8_t>((static_cast<uint8_t>(count_mode_) << 4) | hours_)};
}

void message_59::set_timer(uint8_t hours, uint8_t minutes, uint8_t seconds, mode m)
{
	hours_ = ensure_range(hours, 0, 9);
	minutes_ = ensure_range(minutes, 0, 59);
	seconds_ = ensure_range(seconds, 0, 59);
	count_mode_ = m;
}
}
}
