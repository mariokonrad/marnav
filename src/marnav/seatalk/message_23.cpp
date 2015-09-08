#include "message_23.hpp"

namespace marnav
{
namespace seatalk
{

message_23::message_23()
	: message(ID)
	, sensor_defective(false)
	, temperature_celsius(0)
	, temperature_fahrenheit(0)
{
}

std::unique_ptr<message> message_23::parse(const raw & data)
{
	if (data.size() != 4)
		throw std::invalid_argument{"invalid number of bytes in message_23::parse"};
	if ((data[1] & 0x0f) != 0x01)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_23>();
	message_23 & msg = static_cast<message_23 &>(*result);

	msg.sensor_defective = (data[1] & 0x40) != 0;
	msg.temperature_celsius = data[2];
	msg.temperature_fahrenheit = data[3];

	return result;
}

raw message_23::get_data() const
{
	uint8_t attr = 0x01;

	if (sensor_defective)
		attr |= 0x40;

	return raw{static_cast<uint8_t>(ID), attr, static_cast<uint8_t>(temperature_celsius),
		static_cast<uint8_t>(temperature_fahrenheit)};
}
}
}
