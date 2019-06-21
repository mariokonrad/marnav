#include <marnav/seatalk/message_53.hpp>
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_53::message_53()
	: message(ID)
	, cog_(0.0)
{
}

std::unique_ptr<message> message_53::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_53>();
	message_53 & msg = static_cast<message_53 &>(*result);

	//  53  U0 VW
	// raw   1  2

	double cog = 0;
	cog += static_cast<double>((data[1] >> 4) & 0x03) * 90.0;
	cog += static_cast<double>(data[2] & 0x3f) * 2.0;
	cog += static_cast<double>((data[1] >> 4) & 0x0c) / 8.0;

	msg.cog_ = cog;

	return result;
}

raw message_53::get_data() const
{
	const uint8_t u1 = static_cast<uint8_t>(cog_ / 90.0) & 0x03;
	const uint8_t u2 = static_cast<uint8_t>(std::fmod(cog_, 2.0) * 8.0) & 0x0c;
	const uint8_t vw = static_cast<uint8_t>(std::fmod(cog_, 90.0) / 2.0) & 0x3f;

	return raw{static_cast<uint8_t>(ID), static_cast<uint8_t>(((u1 + u2) << 4) & 0xf0), vw};
}

void message_53::set_cog(double t) noexcept
{
	cog_ = std::fmod(std::abs(t), 360.0);
}
}
}
