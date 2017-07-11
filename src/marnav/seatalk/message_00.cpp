#include "message_00.hpp"
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_00::message_00()
	: message(ID)
	, anchor_alarm_active_(false)
	, metric_display_units_(false)
	, transducer_defective_(false)
	, depth_alarm_active_(false)
	, shallow_depth_alarm_active_(false)
	, depth_(0)
{
}

std::unique_ptr<message> message_00::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_00>();
	message_00 & msg = static_cast<message_00 &>(*result);

	const uint8_t flags = data[2];
	msg.anchor_alarm_active_ = (flags & 0x80) != 0;
	msg.metric_display_units_ = (flags & 0x40) != 0;
	msg.transducer_defective_ = (flags & 0x04) != 0;
	msg.depth_alarm_active_ = (flags & 0x02) != 0;
	msg.shallow_depth_alarm_active_ = (flags & 0x01) != 0;

	msg.depth_ = 0;
	msg.depth_ += data[4];
	msg.depth_ <<= 8;
	msg.depth_ += data[3];

	return result;
}

raw message_00::get_data() const
{
	uint8_t flags = 0;

	flags |= anchor_alarm_active_ ? 0x80 : 0x00;
	flags |= metric_display_units_ ? 0x40 : 0x00;
	flags |= transducer_defective_ ? 0x04 : 0x00;
	flags |= depth_alarm_active_ ? 0x02 : 0x00;
	flags |= shallow_depth_alarm_active_ ? 0x01 : 0x00;

	return raw{static_cast<uint8_t>(ID), 0x02, flags,
		static_cast<uint8_t>((depth_ >> 0) & 0xff), static_cast<uint8_t>((depth_ >> 8) & 0xff)};
}

double message_00::get_depth_meters() const noexcept
{
	if (transducer_defective_)
		return 0.0;
	return (static_cast<double>(depth_) / 10.0) / 3.2808;
}

void message_00::set_depth_meters(double t) noexcept
{
	if (t <= 0.0) {
		depth_ = 0;
	} else {
		depth_ = static_cast<uint16_t>(std::round(10.0 * (t * 3.2808)));
	}
}
}
}
