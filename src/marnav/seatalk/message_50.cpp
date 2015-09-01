#include "message_50.hpp"

namespace marnav
{
namespace seatalk
{

message_50::message_50()
	: message(ID)
{
}

std::unique_ptr<message> message_50::parse(const raw & data) throw(std::invalid_argument)
{
	if (data.size() != 5)
		throw std::invalid_argument{"invalid number of bytes in message_50::parse"};
	if ((data[1] & 0x0f) != 0x02)
		throw std::invalid_argument{"invalid size specified in message"};

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
		= (m & 0x8000) ? geo::latitude::hemisphere::SOUTH : geo::latitude::hemisphere::NORTH;

	msg.lat = geo::latitude{degrees, minutes, seconds, hemisphere};

	// deliberately ignored 'Z'

	return result;
}

raw message_50::get_data() const
{
	uint16_t m = 0;
	m += lat.minutes() * 100;
	m += (lat.seconds() * 100) / 60;
	if (lat.hem() == geo::latitude::hemisphere::SOUTH)
		m |= 0x8000;

	return raw{static_cast<uint8_t>(ID), 0x02, static_cast<uint8_t>(lat.degrees() & 0xff),
		static_cast<uint8_t>((m >> 8) & 0xff), static_cast<uint8_t>((m >> 0) & 0xff)};
}
}
}
