#include "message_50.hpp"

namespace marnav
{
namespace seatalk
{

message_50::message_50()
	: message(ID)
{
}

std::unique_ptr<message> message_50::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_50>();
	message_50 & msg = static_cast<message_50 &>(*result);

	// 50  Z2  XX  YY  YY
	// raw  1   2   3   4

	const uint32_t degrees = data[2];
	uint32_t m = 0;
	m += data[3];
	m <<= 8;
	m += data[4];

	const uint32_t minutes = (m & 0x7fff) / 100;
	const uint32_t seconds = (((m & 0x7fff) % 100) * 60) / 100;
	const geo::latitude::hemisphere hemisphere
		= (m & 0x8000) ? geo::latitude::hemisphere::south : geo::latitude::hemisphere::north;

	msg.lat_ = geo::latitude{degrees, minutes, seconds, hemisphere};

	// deliberately ignored 'Z'

	return result;
}

raw message_50::get_data() const
{
	uint16_t m = 0;
	m += lat_.minutes() * 100;
	m += static_cast<uint16_t>((lat_.seconds() * 100) / 60);
	if (lat_.hem() == geo::latitude::hemisphere::south)
		m |= 0x8000;

	return raw{static_cast<uint8_t>(ID), 0x02, static_cast<uint8_t>(lat_.degrees() & 0xff),
		static_cast<uint8_t>((m >> 8) & 0xff), static_cast<uint8_t>((m >> 0) & 0xff)};
}
}
}
