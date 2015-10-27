#include "message_26.hpp"
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_26::message_26()
	: message(ID)
	, speed1(0)
	, speed2(0)
	, status(0)
{
}

std::unique_ptr<message> message_26::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_26>();
	message_26 & msg = static_cast<message_26 &>(*result);

	msg.speed1 = 0;
	msg.speed1 += data[2];
	msg.speed1 <<= 8;
	msg.speed1 += data[3];

	msg.speed2 = 0;
	msg.speed2 += data[4];
	msg.speed2 <<= 8;
	msg.speed2 += data[5];

	msg.status = data[6];

	return result;
}

raw message_26::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x04, static_cast<uint8_t>((speed1 >> 8) & 0xff),
		static_cast<uint8_t>((speed1 >> 0) & 0xff), static_cast<uint8_t>((speed2 >> 8) & 0xff),
		static_cast<uint8_t>((speed2 >> 0) & 0xff), status};
}

/// @return Value in knots.
double message_26::get_speed1() const noexcept { return 0.01 * speed1; }

/// @return Value in knots.
double message_26::get_speed2() const noexcept { return 0.01 * speed2; }

void message_26::set_speed1(double t) noexcept { speed1 = std::round(std::abs(t) * 100); }

void message_26::set_speed2(double t) noexcept { speed2 = std::round(std::abs(t) * 100); }

void message_26::set_display_in_mph(bool t) noexcept
{
	if (t) {
		status |= 0x02;
	} else {
		status &= ~0x02;
	}
}

void message_26::set_avg_speed_calc_stopped(bool t) noexcept
{
	if (t) {
		status |= 0x01;
	} else {
		status &= ~0x01;
	}
}

void message_26::set_sensor1_valid(bool t) noexcept
{
	if (t) {
		status |= 0x40;
	} else {
		status &= ~0x40;
	}
}
}
}
