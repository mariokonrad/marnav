#include "message_00.hpp"

namespace seatalk
{

message_00::message_00()
	: message(ID)
	, anchor_alarm_active(false)
	, metric_display_units(false)
	, transducer_defective(false)
	, depth_alarm_active(false)
	, shallow_depth_alarm_active(false)
	, depth(0)
{
}

std::unique_ptr<message> message_00::parse(const raw& data) throw(std::invalid_argument)
{
	if (data.size() != 5)
		throw std::invalid_argument{"invalid number of bytes in message_00::parse"};
	if (data[1] != 0x02)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_00>();
	message_00& msg = static_cast<message_00&>(*result);

	const uint8_t flags = data[2];
	msg.anchor_alarm_active = (flags & 0x80) != 0;
	msg.metric_display_units = (flags & 0x40) != 0;
	msg.transducer_defective = (flags & 0x04) != 0;
	msg.depth_alarm_active = (flags & 0x02) != 0;
	msg.shallow_depth_alarm_active = (flags & 0x01) != 0;

	msg.depth = 0;
	msg.depth += data[4];
	msg.depth <<= 8;
	msg.depth += data[3];

	return result;
}

raw message_00::get_data() const
{
	uint8_t flags = 0;

	flags |= anchor_alarm_active ? 0x80 : 0x00;
	flags |= metric_display_units ? 0x40 : 0x00;
	flags |= transducer_defective ? 0x04 : 0x00;
	flags |= depth_alarm_active ? 0x02 : 0x00;
	flags |= shallow_depth_alarm_active ? 0x01 : 0x00;

	return raw{static_cast<uint8_t>(ID), 0x02, flags, static_cast<uint8_t>((depth >> 0) & 0xff),
			   static_cast<uint8_t>((depth >> 8) & 0xff)};
}

}
