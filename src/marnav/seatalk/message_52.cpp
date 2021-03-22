#include <marnav/seatalk/message_52.hpp>
#include <marnav/math/floatingpoint.hpp>
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_52::message_52()
	: message(ID)
	, sog_(0)
{
}

std::unique_ptr<message> message_52::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = std::make_unique<message_52>();
	message_52 & msg = static_cast<message_52 &>(*result);

	//  52  01 XX XX
	// raw   1  2  3

	msg.sog_ = 0;
	msg.sog_ += data[2];
	msg.sog_ <<= 8;
	msg.sog_ += data[3];

	return result;
}

raw message_52::get_data() const
{
	return raw{static_cast<uint8_t>(ID), 0x01, static_cast<uint8_t>((sog_ >> 8) & 0xff),
		static_cast<uint8_t>((sog_ >> 0) & 0xff)};
}

/// Returns the speed over ground in knots.
double message_52::get_sog() const noexcept
{
	return 0.1 * sog_;
}

/// Sets the speed over ground in knots.
void message_52::set_sog(double t) noexcept
{
	sog_ = math::float_cast<decltype(sog_)>(std::floor(t * 10.0));
}
}
}
