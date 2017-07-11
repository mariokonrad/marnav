#include "message_23.hpp"

namespace marnav
{
namespace seatalk
{

message_23::message_23()
	: message(ID)
	, sensor_defective_(false)
	, temperature_celsius_(0)
	, temperature_fahrenheit_(0)
{
}

std::unique_ptr<message> message_23::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_23>();
	message_23 & msg = static_cast<message_23 &>(*result);

	msg.sensor_defective_ = (data[1] & 0x40) != 0;
	msg.temperature_celsius_ = data[2];
	msg.temperature_fahrenheit_ = data[3];

	return result;
}

raw message_23::get_data() const
{
	uint8_t attr = 0x01;

	if (sensor_defective_)
		attr |= 0x40;

	return raw{static_cast<uint8_t>(ID), attr, static_cast<uint8_t>(temperature_celsius_),
		static_cast<uint8_t>(temperature_fahrenheit_)};
}
}
}
