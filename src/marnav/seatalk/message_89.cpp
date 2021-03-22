#include <marnav/seatalk/message_89.hpp>
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_89::message_89()
	: message(ID)
	, value_(0.0)
{
}

std::unique_ptr<message> message_89::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = std::make_unique<message_89>();
	message_89 & msg = static_cast<message_89 &>(*result);

	//  89 U2 VW XY 2Z
	// raw  1  2  3  4

	double t = 0.0;
	t += 90.0 * ((data[1] & 0x30) >> 4);
	t += 2.0 * (data[2] & 0x3f);
	t += 0.5 * ((data[1] & 0xc0) >> 6);

	msg.value_ = std::fmod(t, 360.0);

	return result;
}

raw message_89::get_data() const
{
	uint8_t u = static_cast<uint8_t>(std::floor(value_ / 90.0)) & 0x03;
	uint8_t vw = static_cast<uint8_t>(std::floor((value_ - (90.0 * u)) / 2.0));
	u += static_cast<uint8_t>(std::floor(std::fmod(value_, 2.0) * 2.0)) << 2;

	return raw{static_cast<uint8_t>(ID), static_cast<uint8_t>(0x02 | (u << 4)), vw, 0x00, 0x20};
}

/// Sets the heading, this value will be truncated to the interval `[0.0 .. 359.5]`,
/// in steps of `0.5` degrees.
///
/// @param[in] t Heading in degrees, steps of `0.5`. The absolute value will be used.
void message_89::set_heading(double t)
{
	value_ = std::fmod(std::fabs(t), 360.0);
}
}
}
