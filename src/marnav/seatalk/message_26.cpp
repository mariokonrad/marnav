#include "message_26.hpp"
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_26::message_26()
	: message(ID)
	, speed1_(0)
	, speed2_(0)
	, status_(0)
{
}

std::unique_ptr<message> message_26::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_26>();
	message_26 & msg = static_cast<message_26 &>(*result);

	msg.speed1_ = 0;
	msg.speed1_ += data[2];
	msg.speed1_ <<= 8;
	msg.speed1_ += data[3];

	msg.speed2_ = 0;
	msg.speed2_ += data[4];
	msg.speed2_ <<= 8;
	msg.speed2_ += data[5];

	msg.status_ = data[6];

	return result;
}

raw message_26::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x04, static_cast<uint8_t>((speed1_ >> 8) & 0xff),
		static_cast<uint8_t>((speed1_ >> 0) & 0xff),
		static_cast<uint8_t>((speed2_ >> 8) & 0xff),
		static_cast<uint8_t>((speed2_ >> 0) & 0xff), status_};
}

/// @return Value in knots.
double message_26::get_speed1() const noexcept
{
	return 0.01 * speed1_;
}

/// @return Value in knots.
double message_26::get_speed2() const noexcept
{
	return 0.01 * speed2_;
}

void message_26::set_speed1(double t) noexcept
{
	speed1_ = std::round(std::abs(t) * 100);
}

void message_26::set_speed2(double t) noexcept
{
	speed2_ = std::round(std::abs(t) * 100);
}

void message_26::set_display_in_mph(bool t) noexcept
{
	if (t) {
		status_ |= 0x02;
	} else {
		status_ &= ~0x02;
	}
}

void message_26::set_avg_speed_calc_stopped(bool t) noexcept
{
	if (t) {
		status_ |= 0x01;
	} else {
		status_ &= ~0x01;
	}
}

void message_26::set_sensor1_valid(bool t) noexcept
{
	if (t) {
		status_ |= 0x40;
	} else {
		status_ &= ~0x40;
	}
}
}
}
