#include <marnav/seatalk/message_56.hpp>

namespace marnav
{
namespace seatalk
{

message_56::message_56()
	: message(ID)
	, year_(0)
	, month_(0)
	, day_(0)
{
}

std::unique_ptr<message> message_56::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_56>();
	message_56 & msg = static_cast<message_56 &>(*result);

	//  56 M1 DD YY
	// raw  1  2  3

	msg.year_ = data[3];
	msg.month_ = (data[1] >> 4) & 0x0f;
	msg.day_ = data[2];

	return result;
}

raw message_56::get_data() const
{
	return raw{static_cast<uint8_t>(ID), static_cast<uint8_t>(0x01 | ((month_ << 4) & 0xf0)),
		day_, year_};
}

/// @todo Test rages of parameters
void message_56::set_date(uint8_t y, uint8_t m, uint8_t d) noexcept
{
	year_ = y;
	month_ = m;
	day_ = d;
}
}
}
